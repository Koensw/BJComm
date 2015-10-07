#include "poller.h"

#include <zmq.hpp>

Poller::Poller(): _items(nullptr) {}
Poller::~Poller() {
    delete[] _items;
}

int Poller::add(CommunicationInterface *interface){
    _interfaces.push_back(interface);
    return _interfaces.size()-1;
}

//TODO: make the implementation faster (we dont use more than 2 sockets most probably though)
void Poller::poll(){
    delete[] _items;
    
    _items = new zmq::pollitem_t[_interfaces.size()];
    for(size_t i=0; i<_interfaces.size(); ++i){
        //return if some interface is not running (this causes busy waiting...)
        if(!_interfaces[i]->isRunning()){
            delete[] _items;
            return;
        }
        _items[i] = {(void *) *(_interfaces[i]->_socket), 0, ZMQ_POLLIN, 0 };
    }

    zmq::poll (_items, _interfaces.size());
}

bool Poller::hasMsg(int id){
    //if no poll before return (ALERT: should not be possible, throw error?)
    if(_items == nullptr) return false;
    
    return _items[id].revents & ZMQ_POLLIN;
    
}