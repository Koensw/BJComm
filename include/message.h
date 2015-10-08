/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

#ifndef _BLUEJAY_MESSAGE_H
#define _BLUEJAY_MESSAGE_H

#include <string>
#include <sstream>

/* Base class for message that can be send/received */
class Message{
public:
    /* Create a message */
    Message();
    Message(std::string type);
    Message(std::string type, std::string data);
    
    /* Set the type */
    void setType(std::string);
    std::string getType();
    
    /* Set the data */
    void setData(std::string);
    std::string getData();
    
    /* Return a stream to read the data */
    std::stringstream getStream();
    
    void clear();
private:
    std::string _type;
    std::string _data;
};

#endif