/**
 * Filesystem lib from boost.
 * See http://www.boost.org/doc/libs/1_56_0/libs/filesystem/doc/tutorial.html
 */
/********************* Header Files ***********************/
/* C++ Headers */
#include <iostream> /* Input/output objects. */
//#include <fstream> /* File operations. */
//#include <sstream> /* String stream. */
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
namespace fs = boost::filesystem;

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
    string fil("./test/gtest_example_primer.cpp");
    string tdir("./test");
    fs::path pf(fil);
    fs::path pd(tdir);

    ASSERT_TRUE(fs::exists(pf));
    ASSERT_TRUE(fs::is_regular_file(pf));
    ASSERT_TRUE(fs::exists(pd));
    ASSERT_FALSE(fs::is_regular_file(pd));
    ASSERT_TRUE(fs::is_directory(pd));
}
TEST(BoostFilesystem, TestDirectoryIterator) {
    typedef std::vector<string> vecS;
    fs::path pd("./src");
    vecS vActual;
    vecS vExpect {"./src/CMakeLists.txt", "./src/class1.cpp", "./src/main.cpp"};

    for (fs::directory_iterator itr(pd); itr != fs::directory_iterator(); ++itr) {
	string path = itr->path().c_str();
	vActual.push_back(path);
    }

    std::sort(vActual.begin(), vActual.end());
    std::sort(vExpect.begin(), vExpect.end());

    for (vecS::const_iterator itA =  vActual.begin(), itE = vExpect.begin();
	    itA != vActual.end(); ++itA, ++itE) {
	ASSERT_STREQ(itE->c_str(), itA->c_str());
    }
}

TEST(BoostFilesystem, TestPathDecomposition) {
    typedef std::vector<string> vecS;
    fs::path pd("./src");
    vecS vActual;
    vecS vExpect {"CMakeLists.txt", "class1.cpp", "main.cpp"};

    for (fs::directory_iterator itr(pd); itr != fs::directory_iterator(); ++itr) {
	string fName = itr->path().filename().c_str();
	vActual.push_back(fName);
    }

    std::sort(vActual.begin(), vActual.end());
    std::sort(vExpect.begin(), vExpect.end());

    for (vecS::const_iterator itA =  vActual.begin(), itE = vExpect.begin();
	    itA != vActual.end(); ++itA, ++itE) {
	ASSERT_STREQ(itE->c_str(), itA->c_str());
    }
}

TEST(BoostFilesystem, TestComposePath) {
    std::string parts[] = {"/usr", "lib", "xorg", "modules", "libfb.so"};
    std::string expect = "/usr/lib/xorg/modules/libfb.so";
    fs::path p;

    for (int i = 0; i < 5; ++i) {
	p /= parts[i].c_str();
    }

    ASSERT_STREQ(expect.c_str(), p.c_str());
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
