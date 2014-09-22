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
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>

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
TEST(BoostFilesystem, TestFilesize) {
    string fil("./test/gtest_example_primer.cpp");
    ASSERT_EQ(3666, boost::filesystem::file_size(fil));

    ASSERT_THROW(boost::filesystem::file_size("."),
	boost::filesystem::filesystem_error);
}

TEST(BoostFilesystem, TestQueries) {
    using boost::filesystem::exists;
    using boost::filesystem::is_regular_file;
    using boost::filesystem::path;
    using boost::filesystem::is_directory;

    string fil("./test/gtest_example_primer.cpp");
    string tdir("./test");
    path pf(fil);
    path pd(tdir);

    ASSERT_TRUE(exists(pf));
    ASSERT_TRUE(is_regular_file(pf));
    ASSERT_TRUE(exists(pd));
    ASSERT_FALSE(is_regular_file(pd));
    ASSERT_TRUE(is_directory(pd));
}

TEST(BoostFilesystem, TestDirectoryIterator) {
    using boost::filesystem::directory_iterator;
    using boost::filesystem::directory_entry;
    using std::ostream_iterator;

    boost::filesystem::path pd("./test");
    std::vector<string> vActual;
    std::vector<string> vExpect {"\"./test/gtest_example_primer.cpp\"", "\"./test/test_foreach.cpp\"", "\"./test/test_filesystem.cpp\"", "\"./test/CMakeLists.txt\"", "\"./test/test_main.cpp\"", "\"./test/test_circle_buffer.cpp\""};

    for (directory_iterator itr(pd); itr != directory_iterator(); ++itr) {
	std::stringstream ss;
	ss << *itr;
	vActual.push_back(ss.str());
    }

    std::sort(vActual.begin(), vActual.end());
    std::sort(vExpect.begin(), vExpect.end());

    for ( std::vector<string>::const_iterator itA =  vActual.begin(), itE = vExpect.begin() ; itA != vActual.end(); ++itA, ++itE) {
	ASSERT_STREQ(itE->c_str(), itA->c_str());
    }
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
