#include "poller.h"

#include <zmq.hpp>

int Poller::add(CommunicationInterface *interface){
    _interfaces.push_back(interface);
    return _interfaces.size();
}

//TODO: make the implementation faster (we dont use more than 2 sockets most probably though)
int Poller::poll(){
    zmq::pollitem_t *items = new zmq::pollitem_t[_interfaces.size()];
    for(size_t i=0; i<_interfaces.size(); ++i){
        //return an error if interface is not running (WARNING: make sure that interfaces are initialized before polling)
        if(!_interfaces[i]->_state) return -1;
        items[i] = {(void *) *(_interfaces[i]->_socket), 0, ZMQ_POLLIN, 0 };
    }

    zmq::poll (items, _interfaces.size());
    
    for(size_t i=0; i<_interfaces.size(); ++i){
        if(items[i].revents & ZMQ_POLLIN) return i;
    }
    //return an error if no interface polled (ALERT: should be impossible)
    return -1;
}