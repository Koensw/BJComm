#include "message.h"

#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include <iostream>

using namespace bjcomm;
using namespace boost::algorithm;

Message::Message():
    _type("default"), _data(""), _stream_saver(0) {}

Message::Message(std::string type):
    _type(type), _data(""), _stream_saver(0)
{
    trim(_type);
    if(_type.empty()) _type = "default";
}

Message::Message(std::string type, std::string data): 
    _type(type), _data(data), _stream_saver(0)
{
    trim(_type);
    if(_type.empty()) _type = "default";
    trim(_data);
}
    
Message::~Message(){
    delete _stream_saver;
}    

Message::Message(const Message &msg): _type(msg._type), _data(msg._data) {
    delete _stream_saver;
    _stream_saver = new std::istringstream(_data);
}

Message &Message::operator=(const Message &msg){
    if (this == &msg) return *this; 
    delete _stream_saver;
    _type = msg._type;
    _data = msg._data;
    _stream_saver = new std::istringstream(_data);
    return *this;
}

void Message::setType(std::string type){
    trim(type);
    if(type.empty()) type = "default";
    _type = type;
}

std::string Message::getType() const{
    return _type;
}    
    
void Message::setData(std::string data){
    trim(data);
    _data = data;
}

std::string Message::getData() const{
    return _data;
}

std::istringstream &Message::getStream(){
    delete _stream_saver;
    _stream_saver  = new std::istringstream(_data);
    return *_stream_saver;
}

void Message::clear(){
    _data.clear();
}