#include "subscriber.h"

#include <thread>
#include <chrono>

#include <zmq.hpp>
#include <boost/algorithm/string.hpp>

#include "error.h"

using namespace bjcomm;
using namespace boost::algorithm;

Subscriber::Subscriber(std::string address): 
    _address(address) {}
    
bool Subscriber::start(){
    //if already started return
    if(_running) return false;
    
    _socket = new zmq::socket_t (_context, ZMQ_SUB);
    
    //try to bind socket and set options
    try{
        _socket->bind(_address.c_str());

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
