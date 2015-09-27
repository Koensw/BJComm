cmake_minimum_required(VERSION 2.8.9)
project(bjcomm)

# add java support
find_package(Java REQUIRED)
include(UseJava)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (NOT (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.9 or greater.")
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else ()
    message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif ()

# set compiler and flags
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
# set(CMAKE_JAVA_INCLUDE_PATH /usr/local/share/java/zmq.jar)
set(CMAKE_JAVA_INCLUDE_PATH "/usr/local/share/java/zmq.jar:${CMAKE_CURRENT_BINARY_DIR}/bjcomm_java.jar")
add_jar(bjcomm_java
    SOURCES
    src/java/CommunicationInterface.java
    src/java/Message.java
    src/java/Subscriber.java
    src/java/Publisher.java
    src/java/Poller.java
    src/java/CommunicationError.java
    MANIFEST
    ${CMAKE_SOURCE_DIR}/src/java/MANIFEST.MF
    OUTPUT_NAME
    bjcomm
)

# tests
add_executable(comm_test
    test/test.cpp
)
target_link_libraries(comm_test bjcomm)

add_executable(comm_test_server
    test/test_server.cpp
)
target_link_libraries(comm_test_server bjcomm)

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

# (re)build docs
create_javadoc(bjcomm_docs
    FILES 
    src/java/CommunicationInterface.java
    src/java/Message.java
    src/java/Subscriber.java
    src/java/Publisher.java
    src/java/Poller.java
    src/java/CommunicationError.java
    SOURCEPATH "${CMAKE_CURRENT_SOURCE_DIR}/src/java/"
    CLASSPATH "${CMAKE_JAVA_INCLUDE_PATH}"
    INSTALLPATH "${CMAKE_CURRENT_BINARY_DIR}/"
)
