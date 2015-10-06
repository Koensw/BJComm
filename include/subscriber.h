#ifndef _BLUEJAY_SUBSCRIBER_H
#define _BLUEJAY_SUBSCRIBER_H

#include <string>
#include <zmq.hpp>

#include "message.h"
#include "interface.h"

//WARNING: not thread-safe on its own
class Subscriber: public CommunicationInterface{
public:
    Subscriber(std::string address);
    
    bool start();
    
    Message receive();
    
    //TODO: addAddress(string) - add extra addrees to connect
    //TODO: addMessageType(string) - add message to read (defaults reads all)
private:
    std::string _address;
};

#endif