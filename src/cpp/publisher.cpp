#include "publisher.h"

#include <thread>
#include <chrono>

#include <zmq.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;

Publisher::Publisher(std::string address): 
    _address(address) {}
    
bool Publisher::start(){
    //if already started, stop first and then restart
    if(_state) stop();
    
    _socket = new zmq::socket_t (_context, ZMQ_PUB);
    
    //try to connect to socket
    try{
        _socket->connect(_address);
    }catch(zmq::error_t &e){
        _socket = 0;
        delete _socket;
        
        return false;
    }
    
    _state = true;
    return true;
}

void Publisher::send(Message &msg){
    //wait forever if no socket started (ALERT: should not happen)
    while(!_state) std::this_thread::sleep_for(std::chrono::seconds(1));
        
    //get message
    std::string str = msg.getType()+" "+msg.getData();
    trim(str);
    
    //block read message
    zmq::message_t zmq_msg(str.size());
    memcpy (zmq_msg.data(), str.data(), str.size());
    _socket->send(zmq_msg);
}