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
#include <cstdlib>
//#include <cstddef>
//#include <cctype>
//#include <cstring>
//#include <cstdio>
//#include <climits>
//#include <cassert>
#include <ctime>

/* Project Headers */
#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <gtest/gtest.h>

/******************* Constants/Macros *********************/
#define MAX_SLEEP_TIME_ms 500

/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;

/******************* Type Definitions *********************/
typedef std::vector<int> queue_t;
typedef std::vector<std::string> vecStr_t;

/****************** Class Definitions *********************/
int randInt() {
    static std::default_random_engine gGenerator;
    static std::uniform_int_distribution<int> gDistribution(0, 32*1024);

    return gDistribution(gGenerator);
}

/* Simple logger wrapper, format: [date] tag: msg\n */
void log(const char* tag, const char* msg) {
    std::stringstream ss;
    ss << "[" << boost::posix_time::second_clock::local_time() << "] "
        << tag << ": " << msg << endl; cout << ss.str();
}

void log(std::string tag, std::string msg) {
    log(tag.c_str(), msg.c_str());
}

template <typename T>
void log(std::string tag, T list) {
    std::stringstream ss;
    for (auto word : list) {
        ss << word << " ";
    }

    log(tag.c_str(), ss.str().c_str());
}

class Thread {
public:
    Thread() : threadRunning(false) { };
    virtual ~Thread() {};

    virtual void execute() = 0;
    virtual void start() = 0;
    inline void stop() { threadRunning = false; }
    inline void join() { thread.join(); }
    inline bool isRunning() { return threadRunning; }

protected:
    bool threadRunning;
    boost::thread thread;
    /* Static to be same accross all instances. */
    static queue_t work;
    static boost::mutex workMutex;
};
boost::mutex Thread::workMutex;
queue_t Thread::work;

class ProducerTryLock : public Thread {
public:
    virtual void start() {
        threadRunning = true;
        this->thread = boost::thread(&ProducerTryLock::execute, this);
    }
    virtual void execute() {
        while (threadRunning) {
            if (workMutex.try_lock()) {
                int val = randInt();
                work.push_back(val);

                std::stringstream ss;
                ss << val;
                log("Producer", ss.str().c_str());

                boost::posix_time::milliseconds delay(50);
                boost::this_thread::sleep(delay);
                workMutex.unlock();
            } else {
                log("Producer", "---");
            }

            // Slow things down a little
            boost::posix_time::milliseconds delayTime(randInt() % MAX_SLEEP_TIME_ms);
            boost::this_thread::sleep(delayTime);
        }
    }
};

class ConsumerTryLock : public Thread {
public:
    virtual void start() {
        threadRunning = true;
        this->thread = boost::thread(&ConsumerTryLock::execute, this);
    }
    virtual void execute() {
        while (threadRunning) {
            if (workMutex.try_lock()) {
                if (work.size()) {
                    int val = work.back();
                    work.pop_back();

                    std::stringstream ss;
                    ss << val;
                    log("Consumer", ss.str().c_str());
                }

                boost::posix_time::milliseconds delay(50);
                boost::this_thread::sleep(delay);
                workMutex.unlock();
            } else {
                log("Consumer", "---");
            }

            // Slow things down a little
            boost::posix_time::milliseconds delayTime(randInt() % MAX_SLEEP_TIME_ms);
            boost::this_thread::sleep(delayTime);
        }
    }
};

/****************** Global Functions **********************/
TEST(BoostThread, AcquireMutex) {
    std::srand(std::time(NULL));
    ProducerTryLock producer;
    ConsumerTryLock consumer;
    producer.start();
    consumer.start();

    boost::posix_time::milliseconds workTime(2000);
    boost::this_thread::sleep(workTime);

    log("AcquireMutex", "Shutting down Producer");
    producer.stop();
    producer.join();

    boost::this_thread::sleep(workTime);
    log("AcquireMutex", "Shutting down Consumer");
    consumer.stop();
    consumer.join();
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
