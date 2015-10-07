#include "publisher.h"

#include <thread>
#include <chrono>

#include <zmq.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;

Publisher::Publisher(std::string address): 
    _address(address) {}
    
bool Publisher::start(){
    //if already started return (ALERT: should not happen)
    if(_running) return false;
    
    _socket = new zmq::socket_t (_context, ZMQ_PUB);
    
    //try to connect to socket
    try{
        _socket->connect(_address);
    }catch(zmq::error_t &e){
        delete _socket;
        _socket = 0;
        
        return false;
    }
    
    _running = true;
    return true;
}

void Publisher::send(Message &msg){
    //wait forever if no socket started (ALERT: should not happen)
    while(!_running) std::this_thread::sleep_for(std::chrono::seconds(1));
        
    //get message
    std::string str = msg.getType()+" "+msg.getData();
    trim(str);
    
    //send message
    zmq::message_t zmq_msg(str.size());
    memcpy (zmq_msg.data(), str.data(), str.size());
    _socket->send(zmq_msg);
}