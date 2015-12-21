#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

#include <zmq.hpp>

#include "publisher.h"
#include "message.h"

using namespace bjcomm;

/* Test of a default publisher client */
int main(){
    Publisher pub("test/test_cpp");
    bool ret = pub.start();
    std::cout << "Started " << ret << std::endl;
    
    for(int i=0; true; ++i){
        Message msg("position");
        
        int x = i, y = 1, z = 1;
        std::stringstream sstr;
        sstr << x << " " << y << " " << z;
        msg.setData(sstr.str());
        
        pub.send(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}