#include "message.h"

#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;

Message::Message():
    _type("default"), _data("") {}

Message::Message(std::string type):
    _type(type), _data("") 
{
    trim(_type);
    if(_type.empty()) _type = "default";
}

Message::Message(std::string type, std::string data): 
    _type(type), _data(data)
{
    trim(_type);
    if(_type.empty()) _type = "default";
    trim(_data);
}
    
void Message::setType(std::string type){
    trim(type);
    if(type.empty()) type = "default";
    _type = type;
}

std::string Message::getType(){
    return _type;
}    
    
void Message::setData(std::string data){
    trim(data);
    _data = data;
}

std::string Message::getData(){
    return _data;
}

std::stringstream Message::getStream(){
    return std::stringstream(_data);
}

void Message::clear(){
    _data.clear();
}