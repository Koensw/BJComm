//
//  Weather update server in C++
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

#include <zmq.hpp>

#include "publisher.h"
#include "message.h"

int main(){
    Publisher pub("tcp://localhost:5556");
    bool ret = pub.start();
    std::cout << "Started " << ret << std::endl;
    
    for(int i=0; true; ++i){
        Message msg("position");
        
        int x = i, y = 25, z = 1;
        std::stringstream sstr;
        sstr << x << " " << y << " " << z;
        std::cout << sstr.str() << std::endl;
        msg.setData(sstr.str());
        
        pub.send(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}