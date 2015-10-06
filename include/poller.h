#ifndef _BLUEJAY_POLLER_H
#define _BLUEJAY_POLLER_H

#include <vector>

#include "interface.h"

class Poller{
public:
    int add(CommunicationInterface *);
    //TODO: add remove...
    
    int poll();
private:
    std::vector<CommunicationInterface*> _interfaces;
};

#endif