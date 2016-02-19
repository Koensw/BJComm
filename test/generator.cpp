#include "publisher.h"
#include "message.h"
#include <thread>
#include <iostream>

using namespace bjcomm;

int main(int argc, char *argv[]) {
    std::string channel;
    std::string type;
    std::string message;
    if (argc > 2) {
        channel = std::string(argv[1]);
        type = std::string(argv[2]);
    }
    else {
        std::cout << "Invalid syntax, usage: generator [channel] [type]" << std::endl;
        return 1;
    }

    Publisher pub(channel);
    pub.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::string line;
    std::stringstream data;
    while (std::getline(std::cin, line)) {
        data << line << std::endl;
    }
    Message msg(type);
    msg.setData(data.str());
    pub.send(msg);
    return 0;
}
