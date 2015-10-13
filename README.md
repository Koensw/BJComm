# BJComm #
Library that support communication between layers. Build on top of ZeroMQ.

## Setup ##
To install the libraries and bindings the following steps are needed

1. Install g++-4.9 or later (for Raspberry Pi follow [this](https://solarianprogrammer.com/2015/01/13/raspberry-pi-raspbian-install-gcc-compile-cpp-14-programs/) tutorial)
2. Download libzmq from [here](http://zeromq.org/intro:get-the-software) here and follow the instructions (on Raspberry Pi run ./configure --without-libsodium)
3. Download jzmq from [here](https://github.com/zeromq/jzmq) and follow the build instructions
4. Download cppzmq from [here](https://github.com/zeromq/cppzmq) and move the zmq.hpp folder to the system include folder (normally /usr/local/include/ is a good choice)
5. Download this repo
6. Run ./compile.sh to compile the sources
7. Run ./test.sh to check if everything works correctly

## TODO ##
* add simple debug logger (registers everything)
* add service listener
* add java unit tests
* create auto build scripts
