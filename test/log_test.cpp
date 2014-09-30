/**
 * Template C++ file.
 * Function with references to pointers: func(int *&ptr);
 */
/********************* Header Files ***********************/
/* C++ Headers */
#include <iostream> /* Input/output objects. */
#include <fstream> /* File operations. */
//#include <sstream> [> String stream. <]
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
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/move/utility.hpp>
#include <gtest/gtest.h>

/******************* Constants/Macros *********************/
#define SAMPLE_LOG "sample.log"

/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;
namespace blog = boost::log;
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

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(myLogger, src::logger_mt)

/****************** Class Definitions *********************/
class BoostLogging : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
        boost::log::core::get()->reset_filter();
        //if (boost::filesystem::exists(SAMPLE_LOG)) {
            //std::remove(SAMPLE_LOG);
        //}
        //if (boost::filesystem::exists("sample_0.log")) {
            //std::remove("sample_0.log");
        //}
    }
private:
};

/****************** Global Functions **********************/
void checkLog(const string & file, const std::vector<string> & expected) {
    string line;
    std::ifstream logIn(file);
    std::vector<string> actual;

    while (std::getline(logIn, line)) {
        actual.push_back(line);
    }

    std::vector<string>::const_iterator itrE = expected.begin();
    ASSERT_EQ(expected.size(), actual.size());
    for (std::vector<string>::const_iterator itrA = actual.begin();
            itrA != actual.end(); ++itrA, ++itrE) {
        ASSERT_STREQ(itrE->c_str(), itrA->c_str());
    }
}

/* Trivial logs to cout by deault */
TEST_F(BoostLogging, Trivial) {
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}

TEST_F(BoostLogging, LoggingFilters) {
    /* Only print stuff above debug */
    boost::log::core::get()->set_filter(
            blog::trivial::severity >= blog::trivial::info);

    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}

TEST_F(BoostLogging, FileLog) {
    blog::add_file_log("sample.log");
    blog::core::get()->set_filter(
        blog::trivial::severity > blog::trivial::info
    );

    blog::add_common_attributes();
    src::severity_logger<blog::trivial::severity_level> lg;

    BOOST_LOG_SEV(lg, blog::trivial::fatal) << "A fatal severity message";
}

TEST_F(BoostLogging, FileLogKeywords) {
    blog::add_file_log(
            blog::keywords::file_name = "sample_%N.log",
            blog::keywords::rotation_size = 10 * 1024 * 1024,
            blog::keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
            blog::keywords::format = "[%TimeStamp%]: %Message%"
    );

    blog::core::get()->set_filter(
        blog::trivial::severity > blog::trivial::info
    );

    blog::add_common_attributes();
    src::severity_logger<blog::trivial::severity_level> lg;

    BOOST_LOG_SEV(lg, blog::trivial::fatal) << "A fatal severity message";
}

TEST_F(BoostLogging, LoggerObject) {
    blog::add_file_log(
            blog::keywords::file_name = SAMPLE_LOG,
            blog::keywords::rotation_size = 10 * 1024 * 1024,
            blog::keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
            blog::keywords::format = "[%TimeStamp%]: %Message%"
    );
    blog::add_common_attributes();

    src::logger lg;
    blog::record rec = lg.open_record();
    if (rec) {
        blog::record_ostream stream(rec);
        stream << "Hello, world." << endl;
        stream.flush();
        lg.push_record(boost::move(rec));
    }

    //src::logger_mt lg2 = my_logger::get();
    //BOOST_LOG(lg2) << "Greetings from global logger.";
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
