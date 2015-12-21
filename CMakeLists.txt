cmake_minimum_required(VERSION 2.8.9)
project(bjcomm)

# load required packages
find_package(Java REQUIRED)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
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
    message(FATAL_ERROR "C++ compiler does not support C++11.")
endif ()

# set compiler and flags
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -pedantic --std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_JAVA_COMPILE_FLAGS "-Xlint")

#### BUILD ####

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
target_link_libraries(bjcomm ${Boost_FILESYSTEM_LIBRARY} zmq)

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

#### TEST ####
# build examples
add_executable(cpp_sub_example
    docs/examples/test.cpp
)
target_link_libraries(cpp_sub_example bjcomm)

add_executable(cpp_pub_example
    docs/examples/test_server.cpp
)
target_link_libraries(cpp_pub_example bjcomm)

add_jar(java_sub_example
    SOURCES
    docs/examples/Test.java
    INCLUDE_JARS
    bjcomm_java
)
add_jar(java_pub_example
    SOURCES
    docs/examples/TestServer.java
    INCLUDE_JARS
    bjcomm_java
)

# build unit tests
function(add_cpp_test target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} 
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      bjcomm)

    add_test(${target} ${target})
endfunction()

enable_testing()
add_definitions(-DBOOST_TEST_DYN_LINK) 
add_cpp_test(message_test test/message.cpp)
add_cpp_test(subscriber_test test/subscriber.cpp)
add_cpp_test(publisher_test test/publisher.cpp)
add_cpp_test(poller_test test/poller.cpp)

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

#### INSTALL ####
install(TARGETS bjcomm
        RUNTIME DESTINATION /usr/local/bin
        LIBRARY DESTINATION /usr/local/lib
        ARCHIVE DESTINATION /usr/local/lib/static)
install(DIRECTORY include/ DESTINATION /usr/local/include/bjcomm)
install_jar(bjcomm_java /usr/local/share/java/)