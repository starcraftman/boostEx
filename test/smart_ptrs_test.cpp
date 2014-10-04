/**
 * Template C++ file.
 * Function with references to pointers: func(int *&ptr);
 */
/********************* Header Files ***********************/
/* C++ Headers */
#include <iostream> /* Input/output objects. */
//#include <fstream> /* File operations. */
#include <sstream> /* String stream. */
#include <string> /* C++ String class. */
//#include <new> /* Defines bad_malloc exception, new functions. */
//#include <typeinfo> /* Casting header. */
//#include <exception> /* Top level exception header. */
//#include <stdexcept> /* Derived exception classes. */

/* STL Headers */
//#include <vector>
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
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/smart_ptr.hpp>
#include <gtest/gtest.h>
#include "util.hpp"

/******************* Constants/Macros *********************/


/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;
using MyUtil::myLog;

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
class Simple {
public:
    Simple() {
        std::stringstream ss;
        ss << "Sample" << num++;
        name = ss.str();
        myLog(name.c_str(), "Constructor");
    }
    virtual	~Simple() {
        myLog(name.c_str(), "Destructor");
    }
    void process() {
        myLog(name.c_str(), "Doing something random..");
    }
private:
    std::string name;
    static int num;
};
int Simple::num = 0;

void randomDelay(int maxTime) {
    boost::this_thread::disable_interruption di;
    boost::posix_time::milliseconds delay(MyUtil::randInt(maxTime));
    boost::this_thread::sleep(delay);
}

template <typename T>
void worker(std::shared_ptr<T> & ptr) {
    std::stringstream ss, ss2;
    ss << boost::this_thread::get_id();
    ss2 << "Object " << ptr.get() << " has use count " << ptr.use_count();
    myLog(ss2.str().c_str(), ss.str().c_str());

    randomDelay(1000);
    myLog(ss2.str().c_str(), "Delay over");
}

/****************** Global Functions **********************/

TEST(BoostSmartPtrs, ScopedPointers) {
    auto log = std::bind(myLog, "UniquePtr", std::placeholders::_1);
    log("Creating pointer");

    std::unique_ptr<Simple> ptr(new Simple);
    ptr->process();

    boost::scoped_ptr<Simple> ptr2(new Simple);
    ptr2->process();

    /* Delete before end of scope. */
    std::unique_ptr<Simple> ptr3(new Simple);
    ptr3->process();
    ptr3.reset();

    /* Can't reassign unique_ptr */
    std::unique_ptr<Simple> ptr4;
    // ptr4 = ptr3 /* Compile error. */
    ptr4 = std::move(ptr3);

    /* Array support */
    std::unique_ptr<int[]> intPtr(new int[10]);

    log("Exiting scope");
}

TEST(BoostSmartPtrs, SharedPtrs) {
    std::shared_ptr<Simple> obj(new Simple);

    std::stringstream ss, ss2;
    ss << boost::this_thread::get_id();
    ss2 << "Object " << obj.get() << " has use count " << obj.use_count();
    myLog(ss2.str().c_str(), ss.str().c_str());

    boost::thread w1(std::bind(worker<Simple>, obj));
    boost::thread w2(std::bind(worker<Simple>, obj));

    w1.join();
    w2.join();
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
