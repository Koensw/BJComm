#define BOOST_TEST_MODULE Poller
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>

#include "poller.h"
#include "error.h"
#include "subscriber.h"
#include "publisher.h"

using namespace bjcomm;
using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE( error_test ){
    Poller poll;
    
    BOOST_CHECK_THROW(poll.hasMsg(0), std::logic_error);
    BOOST_CHECK_THROW(poll.poll(), CommunicationError);
    BOOST_CHECK_THROW(poll.hasMsg(-1), std::invalid_argument);
    
    Subscriber sub("test/poller_test");
    BOOST_CHECK_EQUAL(poll.add(&sub), -1);
    sub.start();
    int nm = poll.add(&sub);
    BOOST_CHECK(nm != -1);
}

bool check_poll(Poller *poll, int id){
    poll->poll();
    return poll->hasMsg(id);
}

BOOST_AUTO_TEST_CASE( poll_test ){
    Publisher pub("test/poller_test");
    Subscriber sub("test/poller_test");
    
    pub.start();
    sub.start();
    
    Poller poll;
    int nm = poll.add(&sub);
    
    unit_test_monitor_t& monitor = unit_test_monitor_t::instance();
    monitor.p_timeout.set( 1 );
    BOOST_CHECK_THROW(monitor.execute( std::bind(check_poll, &poll, -2)), boost::execution_exception);
    
    Message snd;
    pub.send(snd);
    BOOST_CHECK(monitor.execute( std::bind(check_poll, &poll, nm)));
}