#include "interface.h"

CommunicationInterface::CommunicationInterface():
    _running(false),
    _context(BJCOMM_IO_THREADS),
    _socket(0)
{}

bool CommunicationInterface::stop(){
    //do not do anything if already closed (ALERT: should not happen)
    if(!_running) return false;
    
    //close the socket
    delete _socket;
    
    _socket = 0;
    _running = false;
    return true;
}