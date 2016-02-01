#include "subscriber.h"

#include <thread>
#include <chrono>

#include <zmq.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <sys/stat.h>
#include <libgen.h>
#include <stdio.h>

#include "error.h"

using namespace bjcomm;
using namespace boost::algorithm;
using namespace boost::filesystem;

Subscriber::Subscriber(std::string address): 
    _address(address) {}
    
bool Subscriber::start(){
    //if already started return
    if(_running) return false;
    
    _socket = new zmq::socket_t (_context, ZMQ_SUB);
    
    //try to bind socket and set options
    try{
        //create path to directory if does not exists
        path comm_path(BJCOMM_COMMON_PATH+_address);
        create_directories(comm_path.parent_path());
        
        //bind socket
        _socket->bind(("ipc://"+comm_path.string()).c_str());
        
        //try to set permissions
        try{
            permissions(BJCOMM_COMMON_PATH, perms::owner_all | perms::group_all | perms::others_all);
            permissions(comm_path.parent_path(), perms::owner_all | perms::group_all | perms::others_all);
            permissions(comm_path, perms::owner_all | perms::group_all | perms::others_all);
        }catch(filesystem_error){}

        //FIXME: bind to all sockets, later add possibility to define message types and ignore others
        _socket->setsockopt(ZMQ_SUBSCRIBE, "", 0);
    }catch(zmq::error_t &e){
        delete _socket;
        _socket = 0;
        
        return false;
    }
    
    _running = true;
    return true;
}

Message Subscriber::receive(){
    //throw exception if trying to receive message on closed channel
    if(!_running) throw CommunicationError("Trying to receive message on channel that is not running!");
        
    //block read message
    zmq::message_t zmq_msg;
    _socket->recv(&zmq_msg);
        
    //read type and data
    std::string str(static_cast<char*>(zmq_msg.data()), zmq_msg.size());
    trim(str);
    
    size_t pos = str.find(' ');
    std::string type;
    std::string data;
    if(pos == std::string::npos){
        type = str;
    }else{
        type = str.substr(0, pos);
        data = str.substr(pos);
        trim(data);
    }
    Message msg(type, data);
    
    return msg;
}
