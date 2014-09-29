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
#include <boost/filesystem.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <gtest/gtest.h>

/******************* Constants/Macros *********************/
#define SAMPLE_LOG "sample.log"

/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;
namespace bl = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

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
class BoostLogging : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
        boost::log::core::get()->reset_filter();
    }
private:
};



/****************** Global Functions **********************/
/* Trivial logs to cout by deault */
TEST_F(BoostLogging, Trivial) {
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}

TEST_F(BoostLogging, LoggingFilters) {
    /* Only print stuff above debug */
    boost::log::core::get()->set_filter(
            bl::trivial::severity >= bl::trivial::info);

    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}

TEST_F(BoostLogging, FileLog) {
    bl::add_file_log("sample.log");
    bl::core::get()->set_filter(
        bl::trivial::severity > bl::trivial::info
    );

    bl::add_common_attributes();
    src::severity_logger<bl::trivial::severity_level> lg;

    BOOST_LOG_SEV(lg, bl::trivial::fatal) << "A fatal severity message";
}

TEST_F(BoostLogging, FileLogKeywords) {
    bl::add_file_log(
            bl::keywords::file_name = "sample_%N.log",
            bl::keywords::rotation_size = 10 * 1024 * 1024,
            bl::keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
            bl::keywords::format = "[%TimeStamp%]: %Message%"
    );

    bl::core::get()->set_filter(
        bl::trivial::severity > bl::trivial::info
    );

    bl::add_common_attributes();
    src::severity_logger<bl::trivial::severity_level> lg;

    BOOST_LOG_SEV(lg, bl::trivial::fatal) << "A fatal severity message";
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
