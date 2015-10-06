#ifndef _BLUEJAY_MESSAGE_H
#define _BLUEJAY_MESSAGE_H

#include <string>
#include <sstream>

class Message{
public:
    Message();
    Message(std::string type);
    Message(std::string type, std::string data);
    
    void setType(std::string);
    std::string getType();
    
    void setData(std::string);
    std::string getData();
    
    std::stringstream getStream();
    
    void clear();
private:
    std::string _type;
    std::string _data;
};

#endif