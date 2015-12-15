#include "poller.h"

#include <zmq.hpp>
#include <stdexcept>

#include "error.h"

using namespace bjcomm;

Poller::Poller(): _items(nullptr) {}
Poller::~Poller() {
    delete[] _items;
}

int Poller::add(CommunicationInterface *interface){
    if(!interface->isRunning()) return -1;
    _interfaces.push_back(interface);
    return _interfaces.size()-1;
}

//TODO: make the implementation faster (we dont use more than 2 sockets most probably though)
void Poller::poll(){
    delete[] _items;
    
    //check if interfaces are added
    if(_interfaces.empty()) throw CommunicationError("Polling without any interfaces added!");
    
    _items = new zmq::pollitem_t[_interfaces.size()];
    for(size_t i=0; i<_interfaces.size(); ++i){
        //return if some interface is not running (this causes busy waiting...)
        if(!_interfaces[i]->isRunning()){
            delete[] _items;
            throw CommunicationError("Polling on a channel that is not running!");
        }
        _items[i] = {(void *) *(_interfaces[i]->_socket), 0, ZMQ_POLLIN, 0 };
    }

    zmq::poll (_items, _interfaces.size(), -1);
}

bool Poller::hasMsg(int id){
    //if no poll or invalid id throw error
    if(id < 0 || id >= (int) _interfaces.size()) throw std::invalid_argument("Checking for message of an invalid identifier!");
    else if(_items == nullptr) throw std::logic_error("Checking for a message before poller is called!");
    
    return _items[id].revents & ZMQ_POLLIN;
    
}
