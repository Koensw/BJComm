#define BOOST_TEST_MODULE Subscriber
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>

#include "error.h"
#include "subscriber.h"
#include "publisher.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE( error_test ){
    Subscriber sub("tcp://*:8888");
    
    BOOST_CHECK_EQUAL(sub.isRunning(), false);
    BOOST_CHECK_EQUAL(sub.stop(), false); 
    
    BOOST_CHECK_THROW(sub.receive(), CommunicationError);
    BOOST_CHECK_EQUAL(sub.start(), true);
    BOOST_CHECK_EQUAL(sub.start(), false);
    
    BOOST_CHECK_EQUAL(sub.isRunning(), true);
    
    BOOST_CHECK_EQUAL(sub.stop(), true);
    BOOST_CHECK_EQUAL(sub.stop(), false);
    
    BOOST_CHECK_EQUAL(sub.isRunning(), false);
}

bool check_receive(Subscriber *sub, std::string type, std::string data){
    Message msg = sub->receive();
    return (msg.getType() == type && msg.getData() == data);
}

BOOST_AUTO_TEST_CASE( read_test){
    Publisher pub("tcp://localhost:8888");
    Subscriber sub("tcp://*:8888");
    
    pub.start();
    sub.start();
    
    unit_test_monitor_t& monitor = unit_test_monitor_t::instance();
    monitor.p_timeout.set( 1 );

    // Now call using the execution monitor
    BOOST_CHECK_THROW(monitor.execute( std::bind(check_receive, &sub, "", "")), boost::execution_exception);
    
    Message snd("test", "1 2 3");
    pub.send(snd);

    Message rec;
    BOOST_CHECK(monitor.execute( std::bind(check_receive, &sub, "test", "1 2 3")));
}