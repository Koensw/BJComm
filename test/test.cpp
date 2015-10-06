#include <iostream>
#include <sstream>

#include <zmq.hpp>

#include "subscriber.h"
#include "message.h"
#include "poller.h"

int main(){
    Subscriber sub("tcp://*:5556");
    bool ret = sub.start();
    
    std::cout << "Started " << ret << std::endl;
    
    Poller poller;
    const int SUBSCRIBER = 0;
    poller.add(&sub);
    
    
    while(true){
        int type = poller.poll();
        
        Message msg;
        
        switch(type){
            case SUBSCRIBER:
                msg = sub.receive();
        
                if(msg.getType() == "position"){
                    int x, y, z;
                    msg.getStream() >> x >> y >> z;
                    std::cout << "Set position to (" << x << "," << y << "," << z << ")" << std::endl;
                }else{
                    std::cout << "INCORRECT MESSAGE" << std::endl;
                }
                break;
            default:
                std::cout << "INCORRECT POLL" << std::endl;
        }
    }
}