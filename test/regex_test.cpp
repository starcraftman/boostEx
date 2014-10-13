/**
 * Template C++ file.
 * Function with references to pointers: func(int *&ptr);
 */
/********************* Header Files ***********************/
/* C++ Headers */
#include <iostream> /* Input/output objects. */
//#include <fstream> /* File operations. */
//#include <sstream> /* String stream. */
#include <string> /* C++ String class. */
//#include <exception> /* Top level exception header. */
//#include <stdexcept> /* Some useful common exceptions */
//#include <new> /* Defines bad_malloc exception, new functions. */
//#include <memory> /* std smart pointers like unique_ptr */
//#include <typeinfo> /* Casting header. */
//#include <limits> /* Inspect properties, numeric_limits<int> iLimit; */
//#include <numeric> /* Math accumulators & other ops*/
//#include <functional> /* Function declarations & std::bind */

/* C++11 Only*/
//#include <chrono> /* std::chrono contains timing for threads */
//#include <initializer_list> /* Allows class to take list like {1,2} */
//#include <random> /* Random c++ version */
//#include <regex>
//#include <thread>
//#include <atomic>
//#include <condition_variable>
//#include <mutex>

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
//#include <utility> // Has pair for map, std::swap
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

#include "gtest/gtest.h"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

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

/***************** Constants & Macros *********************/


/****************** Class Definitions *********************/


/************** Global Vars & Functions *******************/
TEST(BoostRegex, StringMatch) {
    const string sub("subject");
    const boost::regex e1("(sub)(.*)");
    ASSERT_TRUE(boost::regex_match(sub, e1));

    boost::smatch sm;
    boost::regex_match(sub.begin(), sub.end(), sm, e1);
    ASSERT_STREQ("ject", sm[2].str().c_str());

    const string card("1111-2222-3333-4444");
    const boost::regex e2("(\\d{4})[- ]?(\\d{4})[- ](\\d{4})[- ](\\d{4})");
    boost::smatch sm2;
    ASSERT_TRUE(boost::regex_match(card, sm2, e2));
    ASSERT_EQ(5, sm2.size());
    ASSERT_STREQ("2222", sm2[2].str().c_str());
}

TEST(BoostRegex, RegexSearch) {
    string s("This subject has a submarine as a subsequence.");
    boost::regex re("\\b(sub)([^ ]*)");
    boost::smatch sm1;
    std::vector<string> actual, expect = { "subject", "submarine", "subsequence." };

    while (boost::regex_search(s, sm1, re)) {
        actual.push_back(sm1.str(1) + sm1.str(2));
        s = sm1.suffix().str();
    }

    ASSERT_EQ(3, actual.size());
    std::vector<string>::const_iterator itE = expect.begin();
    for (auto i : actual) {
        ASSERT_STREQ(itE->c_str(), i.c_str());
        ++itE;
    }
}

TEST(BoostRegex, RegexReplace) {
    string s("This subject has a submarine as a subsequence.");
    string expect("This sub--ject has a sub--marine as a sub--sequence.");
    boost::regex re("\\b(sub)([^ ]*)");

    string actual = boost::regex_replace(s, re, "sub--$2");
    ASSERT_STREQ(expect.c_str(), actual.c_str());

    string result, expect2("This bus has a bus as a bus");
    boost::regex_replace(std::back_inserter(result), s.begin(), s.end(), re, "bus");
    ASSERT_STREQ(expect2.c_str(), result.c_str());
}

TEST(BoostRegex, RegexTokenIterator) {
    /* Use this to split on the re, iterator returns sequences up to re. */
    string s("A bunch of words!");
    boost::regex space("\\s+");
    std::vector<string> actual;
    std::copy(boost::sregex_token_iterator(s.begin(), s.end(), space, -1),
            boost::sregex_token_iterator(), std::back_inserter(actual));

    std::vector<string> expect;
    boost::split(expect, s, boost::is_any_of(" "));
    ASSERT_EQ(expect.size(), actual.size());
    std::vector<string>::const_iterator itE = expect.begin();
    for (auto act : actual) {
        ASSERT_STREQ(itE->c_str(), act.c_str());
        itE++;
    }
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
