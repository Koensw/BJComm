#define BOOST_TEST_MODULE Publisher
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>

#include "error.h"
#include "publisher.h"

using namespace bjcomm;
using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE( error_test ){
    Publisher pub("tcp://localhost:8888");
    
    BOOST_CHECK_EQUAL(pub.isRunning(), false);
    BOOST_CHECK_EQUAL(pub.stop(), false); 
    
    Message msg;
    BOOST_CHECK_THROW(pub.send(msg), CommunicationError);
    BOOST_CHECK_EQUAL(pub.start(), true);
    BOOST_CHECK_EQUAL(pub.start(), false);
    
    BOOST_CHECK_EQUAL(pub.isRunning(), true);
    
    BOOST_CHECK_EQUAL(pub.stop(), true);
    BOOST_CHECK_EQUAL(pub.stop(), false);
    
    BOOST_CHECK_EQUAL(pub.isRunning(), false);
}

bool check_send(Publisher *pub){
    Message msg;
    pub->send(msg);
    return true;
}

BOOST_AUTO_TEST_CASE( send_test){
    Publisher pub("tcp://localhost:8888");
    
    pub.start();    
    unit_test_monitor_t& monitor = unit_test_monitor_t::instance();
    monitor.p_timeout.set( 1 );
    
    BOOST_CHECK(monitor.execute( std::bind(check_send, &pub)));
}