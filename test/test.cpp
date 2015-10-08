#include <iostream>
#include <sstream>

#include <zmq.hpp>

#include "subscriber.h"
#include "message.h"
#include "poller.h"

/* Test of a default subscriber client */
int main(){
    Subscriber sub("tcp://*:5556");
    bool ret = sub.start();
    
    std::cout << "Started " << ret << std::endl;
    
    Poller poller;
    int SUBSCRIBER = poller.add(&sub);
    
    
    while(true){
        poller.poll();        
        
        if(poller.hasMsg(SUBSCRIBER)){
            Message msg;
            msg = sub.receive();
    
            if(msg.getType() == "position"){
                int x, y, z;
                msg.getStream() >> x >> y >> z;
                std::cout << "Set position to (" << x << "," << y << "," << z << ")" << std::endl;
            }else{
                std::cout << "INCORRECT MESSAGE" << std::endl;
            }
        }else{
            std::cout << "INCORRECT POLL" << std::endl;
        }
    }
}