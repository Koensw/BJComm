#ifndef _BLUEJAY_POLLER_H
#define _BLUEJAY_POLLER_H

#include <vector>

#include "interface.h"

class Poller{
public:
    Poller();
    ~Poller();
    
    int add(CommunicationInterface *);
    //TODO: add remove...
    
    void poll();
    bool hasMsg(int);
private:
    std::vector<CommunicationInterface*> _interfaces;
    
    zmq::pollitem_t *_items;
};

#endif