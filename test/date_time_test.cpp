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
namespace greg  = ::boost::gregorian;
namespace pTime = ::boost::posix_time;
namespace lTime = ::boost::local_time;

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
    greg::date date1(2002, greg::Feb, 1);

    ss << date1;
    ASSERT_STREQ("2002-Feb-01", ss.str().c_str());
}

TEST(BoostDateGregorian, Arithmetic) {
    greg::date dateStart(2002, greg::Feb, 1), dateExpect(2004, greg::Feb, 3);
    greg::date dateActual = dateStart + greg::years(2) + greg::days(2);

    datesEqual<greg::date>(dateExpect, dateActual);
}

TEST(BoostDateGregorian, DaysIterator) {
    std::vector<greg::date> vExpect = {greg::date(2002, greg::Feb, 1),
	greg::date(2002, greg::Feb, 2), greg::date(2002, greg::Feb, 3),
	greg::date(2002, greg::Feb, 4), greg::date(2002, greg::Feb, 5),
    };
    greg::date dateStart(2002, greg::Feb, 1), dateEnd(2002, greg::Feb, 6);

    /* Iterate the days from a start to end */
    std::vector<greg::date>::const_iterator itE = vExpect.begin();
    for(greg::day_iterator itA(dateStart); itA != dateEnd; ++itA, ++itE) {
	datesEqual<greg::date>(*itE, *itA);
    }
}

TEST(BoostDateGregorian, DateGenerator) {
    greg::date dateStart(2002, greg::Feb, 1);
    greg::date dateExpect(2002, greg::Feb, 7);
    greg::date dateActual = greg::next_weekday(dateStart, greg::greg_weekday(greg::Thursday));

    datesEqual<greg::date>(dateExpect, dateActual);
}

TEST(BoostDateGregorian, DateNextDay) {
    greg::date dateExpect(2004, greg::Sep, 6);
    typedef greg::nth_day_of_the_week_in_month nth_dow;
    nth_dow laborDay(nth_dow::first, greg::Monday, greg::Sep);

    datesEqual<greg::date>(dateExpect, laborDay.get_date(2004));
}

TEST(BoostDatePosixTime, SimpleCreate) {
    greg::date dateStart(2002, greg::Feb, 1);
    pTime::ptime timeActual(dateStart, pTime::hours(5));
    string expect("2002-Feb-01 05:00:00");
    pTime::ptime timeExpect(pTime::time_from_string(expect));

    datesEqual<pTime::ptime>(timeExpect, timeActual);
}

TEST(BoostDatePosixTime, InputCreate) {
    string expect("2002-Feb-01 05:00:00");
    std::stringstream ss;
    ss << expect;

    pTime::ptime timeExpect(pTime::time_from_string(expect));
    pTime::ptime timeActual;
    ss >> timeActual;

    datesEqual<pTime::ptime>(timeExpect, timeActual);
}

TEST(BoostDateTimeZone, SimpleConversion) {
    lTime::tz_database tzDb;
    tzDb.load_from_file(
	"libs/share/boost/date_time/date_time_zonespec.csv");
    lTime::time_zone_ptr nycTz = tzDb.time_zone_from_region("America/New_York");
    lTime::time_zone_ptr phxTz(new lTime::posix_time_zone("MST-07:00:00"));

    lTime::local_date_time phxDeparture(greg::date(2005, greg::Apr, 2), pTime::hours(23),
	phxTz, lTime::local_date_time::NOT_DATE_TIME_ON_ERROR);
    pTime::time_duration flight_length = pTime::hours(4) + pTime::minutes(30);
    lTime::local_date_time phxArrival = phxDeparture + flight_length;

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
