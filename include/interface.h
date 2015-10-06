#ifndef _BLUEJAY_COMMUNICATION_INTERFACE_H
#define _BLUEJAY_COMMUNICATION_INTERFACE_H

#define BJCOMM_IO_THREADS 1

#include <string>
#include <zmq.hpp>

class CommunicationInterface{
    friend class Poller;
public:
    CommunicationInterface();
    virtual ~CommunicationInterface(){
        if(_state) stop();
    }
    
    bool isRunning(){
        return _state;
    }
    virtual bool start() = 0;
    virtual bool stop();
    
protected:
    /* PREVENT COPY */
    CommunicationInterface(CommunicationInterface const&);              
    void operator=(CommunicationInterface const&);
    
    bool _state;
    
    //TODO: support sharing contexts
    zmq::context_t _context;
    zmq::socket_t *_socket;
};

#endif