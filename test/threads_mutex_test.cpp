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
#include "util.hpp"

/******************* Constants/Macros *********************/
#define MAX_SLEEP_TIME_ms 500

/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;
using MyUtil::myLog;
using MyUtil::randInt;
namespace place = std::placeholders;

/******************* Type Definitions *********************/
typedef std::vector<int> queue_t;
typedef std::vector<std::string> vecStr_t;

/****************** Class Definitions *********************/
class Thread {
public:
    Thread() : threadRunning(true) { }
    virtual ~Thread() {}

    virtual void execute() = 0;
    virtual void start() = 0;
    inline void stop() {
        threadRunning = false;
        thread.join();
    }
    inline bool isRunning() { return threadRunning; }
    /* Sleep for between 0 & maxTime. */
    void randomDelay(int maxTime) {
        boost::this_thread::disable_interruption di;
        boost::posix_time::milliseconds delay(randInt(maxTime));
        boost::this_thread::sleep(delay);
    }

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
protected:
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
protected:
    boost::timed_mutex * tMutex;
};

class LockGuardHold : public TimedLockHolding {
public:
    LockGuardHold(boost::timed_mutex * _tMutex) :
        TimedLockHolding(_tMutex) {}
    virtual void start() {
        threadRunning = true;
        this->thread = boost::thread(&LockGuardHold::execute, this);
    }
    virtual void execute() {
        auto log = std::bind(myLog, "LockGuardHold", place::_1);
        log("Starting");

        while(threadRunning) {
            log("Holding thread for 2 seconds.");

            {
                boost::lock_guard<boost::timed_mutex> guard(*tMutex);
                boost::posix_time::milliseconds holdTime(1110);
                boost::this_thread::sleep(holdTime);
            }
            log("Lock released.");
        }
        log("Finished");
    }
};

class BoostConditional : public ::testing::Test {
protected:
    virtual void SetUp() {
        workerDone = false;
    }

    virtual void TearDown() {
    }

    boost::mutex ioMutex;
    bool workerDone;
    boost::condition_variable condVar;
};

void workFunc(bool * workerDone, boost::condition_variable * cond) {
    auto log = std::bind(myLog, "WorkerFunc", place::_1);
    log("Wait a little..");
    boost::this_thread::sleep(boost::posix_time::seconds(1));

    log("Notify condition var");
    *workerDone = true;
    cond->notify_one();

    log("Waiting more");
    boost::this_thread::sleep(boost::posix_time::seconds(1));
}

/****************** Global Functions **********************/
TEST(BoostMutex, AcquireMutex) {
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
}

TEST(BoostMutex, TimedMutex) {
    boost::timed_mutex tMutex;
    TimedLockHolding timeHold(&tMutex);
    TimedLockTrying timeTry(&tMutex);
    timeHold.start();
    timeTry.start();

    boost::posix_time::milliseconds workTime(6000);
    boost::this_thread::sleep(workTime);

    timeHold.stop();
    timeTry.stop();
}

TEST(BoostMutex, LockGuard) {
    boost::timed_mutex tMutex;
    LockGuardHold timeHold(&tMutex);
    TimedLockTrying timeTry(&tMutex);
    timeHold.start();
    timeTry.start();

    boost::posix_time::milliseconds workTime(6000);
    boost::this_thread::sleep(workTime);

    timeHold.stop();
    timeTry.stop();
}

TEST_F(BoostConditional, SimpleWait) {
    auto log = std::bind(myLog, "SimpleWait", place::_1);
    log("Starting");
    boost::mutex::scoped_lock lock(ioMutex);
    boost::thread workThread(&workFunc, &workerDone, &condVar);

    while (!workerDone) {
        log("Waiting on lock");
        condVar.wait(lock);
    }

    log("Condition Notified");
    workThread.join();
    log("Thread finished");
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
