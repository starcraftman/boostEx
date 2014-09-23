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
//#include <functional> // Functional objects.
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
#include <boost/foreach.hpp>
#include <boost/date_time.hpp>
#include <gtest/gtest.h>

/******************* Constants/Macros *********************/


/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;
namespace d = ::boost::gregorian;

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
void datesEqual(const d::date &dateExpect, const d::date &dateActual) {
    std::stringstream ssA, ssE;

    ssE << dateExpect;
    ssA << dateActual;

    ASSERT_STREQ(ssE.str().c_str(), ssA.str().c_str());
}

TEST(BoostDateTime, DateSimpleCreate) {
    std::stringstream ss;
    d::date date1(2002, d::Feb, 1);

    ss << date1;
    ASSERT_STREQ("2002-Feb-01", ss.str().c_str());
}

TEST(BoostDateTime, DateArithmetic) {
    d::date dateStart(2002, d::Feb, 1), dateExpect(2004, d::Feb, 3);
    d::date dateActual = dateStart + d::years(2) + d::days(2);

    datesEqual(dateExpect, dateActual);
}

TEST(BoostDateTime, DateIterator) {
    std::vector<d::date> vExpect = {d::date(2002, d::Feb, 1),
	d::date(2002, d::Feb, 2), d::date(2002, d::Feb, 3),
	d::date(2002, d::Feb, 4), d::date(2002, d::Feb, 5),
    };
    d::date dateStart(2002, d::Feb, 1), dateEnd(2002, d::Feb, 6);

    /* Iterate the days from a start to end */
    std::vector<d::date>::const_iterator itE = vExpect.begin();
    for(d::day_iterator itA(dateStart); itA != dateEnd; ++itA, ++itE) {
	datesEqual(*itE, *itA);
    }
}

TEST(BoostDateTime, DateGenerator) {
    d::date dateStart(2002, d::Feb, 1);
    d::date dateExpect(2002, d::Feb, 7);
    d::date dateActual = d::next_weekday(dateStart, d::greg_weekday(d::Thursday));

    datesEqual(dateExpect, dateActual);
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
