/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

#ifndef _BLUEJAY_COMMUNICATION_ERROR_H
#define _BLUEJAY_COMMUNICATION_ERROR_H

#include <iostream>

namespace bjcomm{
    /* CommunicationError if severe error occurs while trying to communicate */
    class CommunicationError : public std::exception{
    public:
        CommunicationError(std::string msg): _msg(msg) {} 
        
        const char *what(){
            return _msg.c_str();
        }
    private:
        std::string _msg;
    };
}

#endif