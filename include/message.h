/*
 * Copyright (c) 2015 Blue Jay Eindhoven
 */

#ifndef _BLUEJAY_MESSAGE_H
#define _BLUEJAY_MESSAGE_H

#include <string>
#include <sstream>

namespace bjcomm{
    /* Base class for message that can be send/received */
    class Message{
    public:
        /* Create a message */
        Message();
        Message(std::string type);
        Message(std::string type, std::string data);
        /* Destruct a message */
        ~Message();
        
        /* Copy behaviour */
        Message(const Message &msg);
        Message &operator=(const Message &msg);
        
        /* Set the type */
        void setType(std::string);
        std::string getType() const;
        
        /* Set the data */
        void setData(std::string);
        std::string getData() const;
        
        /* Return a stream to read the data */
        std::istringstream &getStream();
        
        void clear();
    private:
        std::string _type;
        std::string _data;
        
        //FIXME: temporarily solution as long as G++-4.9 does not support stringstream move
        std::istringstream _stream_saver;
    };
}
    
#endif
