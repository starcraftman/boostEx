#ifndef _UTIL_HPP_
#define _UTIL_HPP_

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
#include <random>

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

/******************* Constants/Macros *********************/
#define RANDINT_MAX 64000

/**************** Class/Func Declaration *******************/
namespace MyUtil {
    inline int randInt(int max = RANDINT_MAX) {
        static std::default_random_engine gGenerator;
        static std::uniform_int_distribution<int> gDistribution(0, 1024);
        return gDistribution(gGenerator) % max;
    }

    /* Simple logger wrapper, format: [date] tag: msg\n */
    inline void myLog(const char* const tag, const char* const msg) {
        std::stringstream ss;
        ss << "[" << boost::posix_time::second_clock::local_time() << "] "
            << tag << ": " << msg << std::endl;
        std::cout << ss.str();
        std::cout.flush();
    }

    template <typename T>
    inline void myLogList(const std::string tag, const T list) {
        std::stringstream ss;
        for (auto word : list) {
            ss << word << " ";
        }

        myLog(tag.c_str(), ss.str().c_str());
    }
}
#endif /* _UTIL_HPP_ */
