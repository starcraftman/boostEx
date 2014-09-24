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
namespace d  = ::boost::gregorian;
namespace pt = ::boost::posix_time;
namespace lt = ::boost::local_time;

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
template<typename T>
void datesEqual(const T &expect, const T &actual) {
    std::stringstream ssA, ssE;
    ssE << expect;
    ssA << actual;

    ASSERT_STREQ(ssE.str().c_str(), ssA.str().c_str());
}

TEST(BoostDateGregorian, SimpleCreate) {
    std::stringstream ss;
    d::date date1(2002, d::Feb, 1);

    ss << date1;
    ASSERT_STREQ("2002-Feb-01", ss.str().c_str());
}

TEST(BoostDateGregorian, Arithmetic) {
    d::date dateStart(2002, d::Feb, 1), dateExpect(2004, d::Feb, 3);
    d::date dateActual = dateStart + d::years(2) + d::days(2);

    datesEqual<d::date>(dateExpect, dateActual);
}

TEST(BoostDateGregorian, DaysIterator) {
    std::vector<d::date> vExpect = {d::date(2002, d::Feb, 1),
	d::date(2002, d::Feb, 2), d::date(2002, d::Feb, 3),
	d::date(2002, d::Feb, 4), d::date(2002, d::Feb, 5),
    };
    d::date dateStart(2002, d::Feb, 1), dateEnd(2002, d::Feb, 6);

    /* Iterate the days from a start to end */
    std::vector<d::date>::const_iterator itE = vExpect.begin();
    for(d::day_iterator itA(dateStart); itA != dateEnd; ++itA, ++itE) {
	datesEqual<d::date>(*itE, *itA);
    }
}

TEST(BoostDateGregorian, DateGenerator) {
    d::date dateStart(2002, d::Feb, 1);
    d::date dateExpect(2002, d::Feb, 7);
    d::date dateActual = d::next_weekday(dateStart, d::greg_weekday(d::Thursday));

    datesEqual<d::date>(dateExpect, dateActual);
}

TEST(BoostDateGregorian, DateNextDay) {
    d::date dateExpect(2004, d::Sep, 6);
    typedef d::nth_day_of_the_week_in_month nth_dow;
    nth_dow laborDay(nth_dow::first, d::Monday, d::Sep);

    datesEqual<d::date>(dateExpect, laborDay.get_date(2004));
}

TEST(BoostDatePosixTime, SimpleCreate) {
    d::date dateStart(2002, d::Feb, 1);
    pt::ptime timeActual(dateStart, pt::hours(5));
    string expect("2002-Feb-01 05:00:00");
    pt::ptime timeExpect(pt::time_from_string(expect));

    datesEqual<pt::ptime>(timeExpect, timeActual);
}

TEST(BoostDatePosixTime, InputCreate) {
    string expect("2002-Feb-01 05:00:00");
    std::stringstream ss;
    ss << expect;

    pt::ptime timeExpect(pt::time_from_string(expect));
    pt::ptime timeActual;
    ss >> timeActual;

    datesEqual<pt::ptime>(timeExpect, timeActual);
}

TEST(BoostDateTimeZone, SimpleConversion) {
    lt::tz_database tzDb;
    tzDb.load_from_file(
	"libs/share/boost/date_time/date_time_zonespec.csv");
    lt::time_zone_ptr nycTz = tzDb.time_zone_from_region("America/New_York");
    lt::time_zone_ptr phxTz(new lt::posix_time_zone("MST-07:00:00"));

    lt::local_date_time phxDeparture(d::date(2005, d::Apr, 2), pt::hours(23),
	phxTz, lt::local_date_time::NOT_DATE_TIME_ON_ERROR);
    pt::time_duration flight_length = pt::hours(4) + pt::minutes(30);
    lt::local_date_time phxArrival = phxDeparture + flight_length;

    string tExpectDepartPHX("2005-Apr-02 23:00:00 MST");
    string tExpectArrivalNYC("2005-Apr-03 06:30:00 EDT");
    std::stringstream ssP, ssN;
    ssP << phxDeparture;
    ssN << phxArrival.local_time_in(nycTz);

    ASSERT_STREQ(tExpectDepartPHX.c_str(), ssP.str().c_str());
    ASSERT_STREQ(tExpectArrivalNYC.c_str(), ssN.str().c_str());
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
