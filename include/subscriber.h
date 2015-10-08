/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

#ifndef _BLUEJAY_SUBSCRIBER_H
#define _BLUEJAY_SUBSCRIBER_H

#include <string>

#include "message.h"
#include "interface.h"

/* Interface that receives data from asynchronous channel */
//WARNING: not thread-safe on its own
class Subscriber: public CommunicationInterface{
public:
    Subscriber(std::string address);
    
    /* Start an interface */
    bool start();
    
    /* Receive a message from an interface */
    Message receive();
    
    //TODO: addAddress(string) - add extra address to connect
    //TODO: addMessageType(string) - add message to read (defaults reads all)
private:
    std::string _address;
};

#endif