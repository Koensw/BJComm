cmake_minimum_required(VERSION 2.8.3)
project(bjcomm)

# set compiler and flags
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -pedantic --std=c++11 ${CMAKE_CXX_FLAGS}")

# include the headers
include_directories(include/)

# build the communication bindings for c++
add_library(bjcomm SHARED
    src/cpp/interface.cpp
    src/cpp/message.cpp
    src/cpp/subscriber.cpp
    src/cpp/publisher.cpp
    src/cpp/poller.cpp
)
target_link_libraries(bjcomm zmq)

# example controller
add_executable(comm_test
    test/test.cpp
)

add_executable(comm_test_server
    test/test_server.cpp
)

# link libraries
target_link_libraries(comm_test bjcomm)
target_link_libraries(comm_test_server bjcomm)