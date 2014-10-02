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
#include <functional> // Functional objects.
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
void myLog(const char* const tag, const char* const msg) {
    std::stringstream ss;
    ss << "[" << boost::posix_time::second_clock::local_time() << "] "
        << tag << ": " << msg << endl; cout << ss.str();
}

void log(const std::string tag, const std::string msg) {
    myLog(tag.c_str(), msg.c_str());
}

template <typename T>
void log(const std::string tag, const T list) {
    std::stringstream ss;
    for (auto word : list) {
        ss << word << " ";
    }

    myLog(tag.c_str(), ss.str().c_str());
}

class Thread {
public:
    Thread() : threadRunning(false) { }
    virtual ~Thread() {}

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
queue_t Thread::work;
boost::mutex Thread::workMutex;

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
                myLog("Producer", ss.str().c_str());

                boost::posix_time::milliseconds delay(50);
                boost::this_thread::sleep(delay);
                workMutex.unlock();
            } else {
                myLog("Producer", "---");
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
                    myLog("Consumer", ss.str().c_str());
                }

                boost::posix_time::milliseconds delay(50);
                boost::this_thread::sleep(delay);
                workMutex.unlock();
            } else {
                myLog("Consumer", "---");
            }

            // Slow things down a little
            boost::posix_time::milliseconds delayTime(randInt() % MAX_SLEEP_TIME_ms);
            boost::this_thread::sleep(delayTime);
        }
    }
};

class TimedLockHolding : public Thread {
public:
    TimedLockHolding(boost::timed_mutex * _tMutex) { tMutex = _tMutex; }
    virtual void start() {
        threadRunning = true;
        this->thread = boost::thread(&TimedLockHolding::execute, this);
    }
    virtual void execute() {
        namespace place = std::placeholders;
        auto log = std::bind(myLog, "TimedHolding", place::_1);
        log("Starting");

        while(threadRunning) {
            log("Idling");
            boost::posix_time::milliseconds idleTime(500);
            boost::this_thread::sleep(idleTime);

            log("Locking");
            tMutex->lock();

            log("Working");
            boost::posix_time::milliseconds holdTime(2000);
            boost::this_thread::sleep(holdTime);

            tMutex->unlock();
            log("Unlocked");
        }
        log("Finished");
    }
private:
    boost::timed_mutex * tMutex;
};

class TimedLockTrying : public Thread {
public:
    TimedLockTrying(boost::timed_mutex * _tMutex) { tMutex = _tMutex; }
    virtual void start() {
        threadRunning = true;
        this->thread = boost::thread(&TimedLockTrying::execute, this);
    }
    virtual void execute() {
        namespace place = std::placeholders;
        auto log = std::bind(myLog, "TimedTrying", place::_1);
        log("Starting");

        while(threadRunning) {
            log("Idling");
            boost::posix_time::milliseconds idleTime(600);
            boost::this_thread::sleep(idleTime);

            log("Locking");
            boost::posix_time::time_duration lockTimeout(0, 0, 1); // hours, mins, secs
            if (tMutex->timed_lock(lockTimeout)) {
                log("Working");
                boost::posix_time::milliseconds holdTime(400);
                boost::this_thread::sleep(holdTime);

                tMutex->unlock();
                log("Unlocked");
            } else {
                log(">>> Timedout on lock.");
            }
        }
        log("Finished");
    }
private:
    boost::timed_mutex * tMutex;
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

    myLog("AcquireMutex", "Shutting down Producer");
    producer.stop();

    boost::this_thread::sleep(workTime);
    myLog("AcquireMutex", "Shutting down Consumer");
    consumer.stop();
    consumer.join();
    producer.join();
}

TEST(BoostThread, TimedMutex) {
    boost::timed_mutex tMutex;
    TimedLockHolding timeHold(&tMutex);
    TimedLockTrying timeTry(&tMutex);
    timeHold.start();
    timeTry.start();

    boost::posix_time::milliseconds workTime(6000);
    boost::this_thread::sleep(workTime);

    timeHold.stop();
    timeTry.stop();
    timeHold.join();
    timeTry.join();
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
