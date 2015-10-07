cmake_minimum_required(VERSION 2.8.11)
project(bjcomm)

# add java support
find_package(Java REQUIRED)
include(UseJava)

# set compiler and flags
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -pedantic --std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_JAVA_COMPILE_FLAGS "-Xlint")

# include the headers
include_directories(include/)

# communication bindings for c++
add_library(bjcomm SHARED
    src/cpp/interface.cpp
    src/cpp/message.cpp
    src/cpp/subscriber.cpp
    src/cpp/publisher.cpp
    src/cpp/poller.cpp
)
target_link_libraries(bjcomm zmq)

# communication bindings for java
set(CMAKE_JAVA_INCLUDE_PATH /usr/local/share/java/zmq.jar)
add_jar(bjcomm_java
    SOURCES
    src/java/CommunicationInterface.java
    src/java/Message.java
    src/java/Subscriber.java
    src/java/Publisher.java
    src/java/Poller.java
    MANIFEST 
    ${CMAKE_SOURCE_DIR}/src/java/MANIFEST.MF
    OUTPUT_NAME
    bjcomm
)

# tests
add_executable(comm_test
    test/test.cpp
)

add_executable(comm_test_server
    test/test_server.cpp
)
add_jar(comm_test_java
    SOURCES
    test/Test.java
    INCLUDE_JARS
    bjcomm_java
)
add_jar(comm_test_server_java
    SOURCES
    test/TestServer.java
    INCLUDE_JARS
    bjcomm_java
)

# MANIFEST ${CMAKE_SOURCE_DIR}/test/MANIFEST.MF

# link libraries
target_link_libraries(comm_test bjcomm)
target_link_libraries(comm_test_server bjcomm)