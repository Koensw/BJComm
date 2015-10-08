/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

#ifndef _BLUEJAY_POLLER_H
#define _BLUEJAY_POLLER_H

#include <vector>

#include "interface.h"

/* Simple poller interface to divide load between channels */
class Poller{
public:
    Poller();
    ~Poller();
    
    /* Add an identifier returning the ID (or -1 in case of errors) */
    int add(CommunicationInterface *);
    
    /* Poll for messages */
    void poll();
    
    /* Check if identifier has a message */
    bool hasMsg(int);
private:
    std::vector<CommunicationInterface*> _interfaces;
    
    zmq::pollitem_t *_items;
};

#endif