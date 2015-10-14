/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

#ifndef _BLUEJAY_PUBLISHER_H
#define _BLUEJAY_PUBLISHER_H

#include <string>

#include "interface.h"
#include "message.h"

namespace bjcomm{
    /* Interface that sends data over asynchronous channel */
    class Publisher: public CommunicationInterface{
    public:
        /* Construct a publisher */
        Publisher(std::string address);
        
        /* Try to start the interface */
        bool start();
        
        /* Send a message */
        void send(Message &msg);
    private:
        std::string _address;
    };
}

#endif