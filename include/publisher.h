#ifndef _BLUEJAY_SUBSCRIBER_H
#define _BLUEJAY_SUBSCRIBER_H

#include <string>
#include <zmq.hpp>

#include "interface.h"
#include "message.h"

//WARNING: not thread-safe on its own
class Publisher: public CommunicationInterface{
public:
    Publisher(std::string address);
    
    bool start();
    
    void send(Message &msg);
    
    //TODO: add(Debug)Address(string) - add extra address to write to (useful for debugging) 
private:
    std::string _address;
};
#endif