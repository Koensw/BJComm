#include "subscriber.h"

#include <thread>
#include <chrono>

#include <zmq.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;

Subscriber::Subscriber(std::string address): 
    _address(address) {}
    
bool Subscriber::start(){
    //if already started return (ALERT: should not happen)
    if(_running) return false;
    
    _socket = new zmq::socket_t (_context, ZMQ_SUB);
    
    //try to bind socket and set options
    try{
        _socket->bind(_address);

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
    //wait forever if no socket started (ALERT: should not happen)
    while(!_running) std::this_thread::sleep_for(std::chrono::seconds(1));
        
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