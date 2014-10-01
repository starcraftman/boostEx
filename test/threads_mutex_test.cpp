/**
 * Filesystem lib from boost.
 * See http://www.boost.org/doc/libs/1_56_0/libs/filesystem/doc/tutorial.html
 */
/********************* Header Files ***********************/
/* C++ Headers */
#include <iostream> /* Input/output objects. */
//#include <fstream> /* File operations. */
//#include <sstream> /* String stream. */
#include <string> /* C++ String class. */
//#include <new> /* Defines bad_malloc exception, new functions. */
//#include <typeinfo> /* Casting header. */
//#include <exception> /* Top level exception header. */
//#include <stdexcept> /* Derived exception classes. */
#include <random>

/* STL Headers */
#include <vector>
//#include <list>
//#include <deque>
//#include <stack>
//#include <queue>
//#include <priority_queue>
//#include <bitset>
//#include <set> // multiset for multiple keys allowed.
//#include <map> // multimap for multiple keys allowed.
//#include <utility> // Has pair for map.
//#include <algorithm>
//#include <numeric>
//#include <functional> // Functional objects.
//#include <iterator> // Contains back_inserter function and like.

/* C Headers */
//#include <cstdlib>
//#include <cstddef>
//#include <cctype>
//#include <cstring>
//#include <cstdio>
#include <climits>
//#include <cassert>

/* Project Headers */
#include <boost/date_time.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <gtest/gtest.h>

/******************* Constants/Macros *********************/
#define MAX_SLEEP_TIME_ms 500
std::default_random_engine gGenerator;
std::uniform_int_distribution<long> gDistribution(0, LONG_MAX);

/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;

/******************* Type Definitions *********************/
typedef std::vector<long> queue_t;

/****************** Class Definitions *********************/
long randLong(long max = 0) {
    long val = gDistribution(gGenerator);
    if (max) {
        val = val % max;
    }

    return val;
}

class Worker {
public:
    Worker() : threadRunning(false) { };
    virtual ~Worker() {};

    virtual void execute() = 0;
    virtual void start() = 0;
    void stop() { threadRunning = false; }
    void join() { thread.join(); }
    bool isRunning() { return threadRunning; }

protected:
    bool threadRunning;
    boost::thread thread;
    /* Static to be same accross all instances. */
    static queue_t work;
    static boost::mutex workMutex;
};
boost::mutex Worker::workMutex;
queue_t Worker::work;

class ProducerTryLock : public Worker {
public:
    virtual void start() {
        threadRunning = true;
        this->thread = boost::thread(&ProducerTryLock::execute, this);
    }
    virtual void execute() {
        while (threadRunning) {
            if (workMutex.try_lock()) {
                long val = randLong();
                work.push_back(val);

                printf("^^^ %ld\n", val);

                boost::posix_time::milliseconds delay(50);
                boost::this_thread::sleep(delay);
                workMutex.unlock();
            } else {
                printf("^== \n");
            }

            // Slow things down a little
            boost::posix_time::milliseconds delayTime(randLong() % MAX_SLEEP_TIME_ms);
            boost::this_thread::sleep(delayTime);
        }
    }
};

class ConsumerTryLock : public Worker {
public:
    virtual void start() {
        threadRunning = true;
        this->thread = boost::thread(&ConsumerTryLock::execute, this);
    }
    virtual void execute() {
        while (threadRunning) {
            if (workMutex.try_lock()) {
                if (work.size()) {
                    long val = work.back();
                    work.pop_back();

                    printf("vvv %ld\n", val);
                }

                boost::posix_time::milliseconds delay(50);
                boost::this_thread::sleep(delay);
                workMutex.unlock();
            } else {
                printf("v==\n");
            }

            // Slow things down a little
            boost::posix_time::milliseconds delayTime(randLong() % MAX_SLEEP_TIME_ms);
            boost::this_thread::sleep(delayTime);
        }
    }
};

/****************** Global Functions **********************/
TEST(BoostThread, AcquireMutex) {
    boost::mutex m;
    ProducerTryLock t1;
    ConsumerTryLock t2;
    t1.start();
    t2.start();

    boost::posix_time::milliseconds workTime(2000);
    boost::this_thread::sleep(workTime);

    t1.stop();
    t2.stop();
    t1.join();
    t2.join();
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
