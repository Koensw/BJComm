/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

#ifndef _BLUEJAY_COMMUNICATION_INTERFACE_H
#define _BLUEJAY_COMMUNICATION_INTERFACE_H

#define BJCOMM_COMMON_PATH std::string("/tmp/bluejay/")
#define BJCOMM_IO_THREADS 1

#include <string>
#include <zmq.hpp>

namespace bjcomm{
    /* Base class for communication interfacess*/
    class CommunicationInterface{
        friend class Poller;
    public:
        /* Construct and destruct interface */
        CommunicationInterface();
        virtual ~CommunicationInterface(){
            //try to stop interface
            stop();
        }
        
        /* Return if interface is running */
        bool isRunning(){
            return _running;
        }
        
        /* Start and stop interface */
        virtual bool start() = 0;
        virtual bool stop();
        
    protected:
        /* PREVENT COPY */
        CommunicationInterface(CommunicationInterface const&) = delete;          
        void operator=(CommunicationInterface const&) = delete;
        
        bool _running;
        
        //TODO: support sharing contexts
        zmq::context_t _context;
        zmq::socket_t *_socket;
    };
}

#endif