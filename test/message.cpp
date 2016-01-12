#define BOOST_TEST_MODULE Message
#include <iostream>
#include <boost/test/unit_test.hpp>

#include "message.h"

using namespace bjcomm;

BOOST_AUTO_TEST_CASE( constructor_test ){
    Message msg;
    BOOST_CHECK_EQUAL(msg.getType(), "default");
    BOOST_CHECK_EQUAL(msg.getData(), "");
    
    Message msg2("test");
    BOOST_CHECK_EQUAL(msg2.getType(), "test");
    BOOST_CHECK_EQUAL(msg2.getData(), "");
    
    Message msg3(" test  ");
    BOOST_CHECK_EQUAL(msg3.getType(), "test");
    BOOST_CHECK_EQUAL(msg3.getData(), "");
    
    Message msg4(" test  ", "  data ");
    BOOST_CHECK_EQUAL(msg4.getType(), "test");
    BOOST_CHECK_EQUAL(msg4.getData(), "data");
    
    Message msg5("   ", "  data ");
    BOOST_CHECK_EQUAL(msg5.getType(), "default");
    BOOST_CHECK_EQUAL(msg5.getData(), "data");
}


BOOST_AUTO_TEST_CASE( data_test ) {
    Message msg;
    
    msg.setType("test");
    BOOST_CHECK_EQUAL(msg.getType(), "test");
    BOOST_CHECK_EQUAL(msg.getData(), "");
    
    msg.setType("     ");
    BOOST_CHECK_EQUAL(msg.getType(), "default");
    BOOST_CHECK_EQUAL(msg.getData(), "");
    
    msg.setType("  test ");
    BOOST_CHECK_EQUAL(msg.getType(), "test");
    BOOST_CHECK_EQUAL(msg.getData(), "");
    
    msg.setData("1 2 3");
    BOOST_CHECK_EQUAL(msg.getType(), "test");
    BOOST_CHECK_EQUAL(msg.getData(), "1 2 3");
    
    msg.setData("   1 2 3   \r\n");
    BOOST_CHECK_EQUAL(msg.getType(), "test");
    BOOST_CHECK_EQUAL(msg.getData(), "1 2 3");
    
    msg.setData("   1 2 3\n4");
    BOOST_CHECK_EQUAL(msg.getType(), "test");
    BOOST_CHECK_EQUAL(msg.getData(), "1 2 3\n4");
    
    msg.clear();
    BOOST_CHECK_EQUAL(msg.getType(), "test");
    BOOST_CHECK_EQUAL(msg.getData(), "");
}

BOOST_AUTO_TEST_CASE( stream_test ){
    Message msg;
    msg.setData("1 2 3");
    
    int a, b, c;
    msg.getStream() >> a >> b >> c;
    BOOST_CHECK_EQUAL(a, 1);
    BOOST_CHECK_EQUAL(b, 2);
    BOOST_CHECK_EQUAL(c, 3);
    msg.getStream() >> a >> b >> c;
    BOOST_CHECK_EQUAL(a, 1);
    BOOST_CHECK_EQUAL(b, 2);
    BOOST_CHECK_EQUAL(c, 3);
    
    msg.setData("test");
    msg.getStream() >> a >> b >> c;
    BOOST_CHECK_EQUAL(a, 0);
    
    std::string data;
    msg.getStream() >> data;
    BOOST_CHECK_EQUAL(data, "test");
    
    msg = Message("test_new");
    msg.setData("copy");
    BOOST_CHECK_EQUAL(msg.getData(), "copy");
}

// EOF
