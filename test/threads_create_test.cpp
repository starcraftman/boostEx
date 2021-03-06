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
//#include <cstdlib>
//#include <cstddef>
//#include <cctype>
//#include <cstring>
//#include <cstdio>
//#include <climits>
//#include <cassert>

/* Project Headers */
#include <boost/date_time.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lockable_adapter.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <gtest/gtest.h>
#include "util.hpp"

/******************* Constants/Macros *********************/


/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;

/******************* Type Definitions *********************/
/* For enums: Try to namesapce the common elements.
 * typedef enum {
 *	VAL_,
 * } name_e;
 */

/* For structs:
 * typedef struct name_s {
 *	int index;
 * } name_t;
 */

/****************** Class Definitions *********************/
double computeRoot(double num, double guess, int iterations);

class Worker {
public:
    Worker(double num, double guess, int iterations) :
        _num(num), _guess(guess), _iterations(iterations) { }

    void operator()() {
        double x = _guess;
        for (int i = 0; i < _iterations; ++i) {
            double fX = (x * x) - _num;
            x = x - (fX / (2 * x));
        }
        std::printf("The root of %f is %f.\n", _num, x);
    }

private:
    double _num, _guess;
    int _iterations;
};

class WorkerObj {
public:
    WorkerObj(double num, double guess, int iterations) :
        _num(num), _guess(guess), _iterations(iterations) { }

    void computeRoot() {
        cout << "Worker Started." << endl;
        double x = _guess;
        for (int i = 0; i < _iterations; ++i) {
            double fX = (x * x) - _num;
            x = x - (fX / (2 * x));
        }
        std::printf("The root of %f is %f.\n", _num, x);
    }

    void start() {
        _thread = boost::thread(&WorkerObj::computeRoot, this);
    }

    void join() {
        _thread.join();
    }

private:
    double _num, _guess;
    int _iterations;
    boost::thread  _thread;
};

/****************** Global Functions **********************/
/* Simple test func. */
static void workerFunc1(string &msg) {
    boost::posix_time::seconds workTime(1);

    cout << "Worker: Running." << endl;
    cout << msg << endl;
    boost::this_thread::sleep(workTime);
    cout << "Worker: Finished." << endl;
}

static double computeRoot(int num, double guess, int iters) {
    double x = guess;
    for (int i = 0; i < iters; ++i) {
        double fX = (x * x) - num;
        x = x - (fX / (2 * x));
    }

    return x;
}

static void dummy() {
    namespace place = std::placeholders;
    auto log = std::bind(MyUtil::myLog, "DummyFunc", place::_1);
    log("Starting");

    boost::posix_time::milliseconds delay(1100);
    boost::this_thread::sleep(delay);

    log("Finished");
}

TEST(BoostThreads, SimpleExecute) {
    cout << endl << "Main: Startup." << endl;

    boost::thread w1(workerFunc1, string("Hello there."));
    cout << "Main: Waiting." << endl;
    w1.join();
    cout << "Main: Finished." << endl;
}

TEST(BoostThreads, ComputeRoot) {
    cout << endl << "Main: Startup." << endl;

    Worker worker(612, 10, 10);
    boost::thread workThread(worker);
    cout << "Main: Waiting." << endl;
    workThread.join();
    cout << "Main: Finished." << endl;
}

TEST(BoostThreads, ObjectThreadWorker) {
    cout << endl << "Main: Startup." << endl;

    WorkerObj worker(900, 15, 10);
    worker.start();
    cout << "Main: Waiting." << endl;
    worker.join();
    cout << "Main: Finished." << endl;
}

TEST(BoostThreads, ThreadAttributes) {
    boost::thread::attributes attrs;
    std::size_t t_stackSize = attrs.get_stack_size();
    attrs.set_stack_size(t_stackSize * 2);

    boost::thread t(dummy);
    cout << "ThreadAttributes" << t.get_id() << endl;
}

TEST(BoostThreads, ScopedThread) {
    /* Scoped threads join on losing focus. */
    MyUtil::myLog("ScopedThread", "Creating Thread");
    boost::scoped_thread<> t((boost::thread(dummy)));
    MyUtil::myLog("ScopedThread", "Going Out Of Scope");
}
/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
