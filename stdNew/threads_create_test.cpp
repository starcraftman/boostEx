/**
 * Filesystem lib from boost.
 * See http://www.boost.org/doc/libs/1_56_0/libs/filesystem/doc/tutorial.html
 */
/********************* Header Files ***********************/
/* C++ Headers */
#include <iostream> /* Input/output objects. */
//#include <fstream> /* File operations. */
#include <sstream> /* String stream. */
#include <string> /* C++ String class. */
//#include <exception> /* Top level exception header. */
//#include <stdexcept> /* Some useful common exceptions */
//#include <new> /* Defines bad_malloc exception, new functions. */
//#include <memory> /* std smart pointers like unique_ptr */
//#include <typeinfo> /* Casting header. */
//#include <limits> /* Inspect properties, numeric_limits<int> iLimit; */
//#include <numeric> /* Math accumulators & other ops*/
#include <functional> /* Function declarations & std::bind */

/* C++11 Only*/
#include <chrono> /* std::chrono contains timing for threads */
//#include <initializer_list> /* Allows class to take list like {1,2} */
//#include <random> /* Random c++ version */
#include <thread>
//#include <atomic>
#include <condition_variable>
#include <mutex>

/* STL Headers */
//#include <vector>
//#include <list>
//#include <deque>
//#include <stack>
//#include <queue>
//#include <priority_queue>
//#include <set> // multiset for multiple keys allowed.
//#include <map> // multimap for multiple keys allowed.
//#include <bitset>
//#include <utility> // Has pair for map.
//#include <algorithm>
//#include <iterator> // Contains back_inserter function and like.

/* C Headers */
//#include <cstdio>
//#include <cstring>
//#include <cstdlib> /* atof, rand, malloc... */
//#include <cstddef> /* size_t, NULL */
//#include <cstdarg> /* Variable argument functions */
//#include <cctype> /* Character check functions */
//#include <climits>
//#include <cassert>
//$include <cmath>
//$include <cstdint> /* C++11 only, standard u_int16 & such */

/* Project Headers */
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

/****************** Global Functions **********************/
/* Sjimple test func. */
static void worker1(const string &msg) {
    const auto log = std::bind(MyUtil::myLog, "Worker1", std::placeholders::_1);

    cout << msg << endl;

    log("Working...");
    const std::chrono::milliseconds workTime(1000);
    std::this_thread::sleep_for(workTime);
    log("Finished");
}

static double computeRoot(int num, double guess, int iters) {
    double x = guess;
    for (int i = 0; i < iters; ++i) {
        double fX = (x * x) - num;
        x = x - (fX / (2 * x));
    }

    return x;
}

static void worker2() {
    std::stringstream ss;
    ss << "The root of " << 6822 << " is " << computeRoot(6822, 20, 10);
    MyUtil::myLog("Worker2", ss.str().c_str());
}

TEST(StdThreads, SimpleExecute) {
    const auto log = std::bind(MyUtil::myLog, "SimpleExecute", std::placeholders::_1);
    log("Starting");

    string msg("Hello world.");
    std::thread worker(worker1, std::ref(msg));
    log("Waiting on thread");
    worker.join();
    log("Finished");
}

TEST(StdThreads, ComputeRoot) {
    const auto log = std::bind(MyUtil::myLog, "StdThreads", std::placeholders::_1);
    log("Starting");

    std::thread worker(worker2);
    log("Waiting on thread");
    worker.join();
    log("Finished");
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
