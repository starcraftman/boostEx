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
#include <boost/circular_buffer.hpp>
#include <boost/foreach.hpp>
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
class BoostCircleTest : public ::testing::Test {
protected:
    virtual void SetUp() {
	cb.resize(3);
	int vals[] = {1, 2, 3};

	for (int i = 0; i < 3; ++i) {
	    cb.push_back(vals[i]);
	}
    }

    virtual void TearDown() {
    }

    boost::circular_buffer<int> cb;
};

/****************** Global Functions **********************/

TEST_F(BoostCircleTest, CircleOverwrite) {
    EXPECT_EQ(3, cb[2]);
    cb.push_back(55);
    EXPECT_EQ(55, cb.back());
    cb.push_back(22);
    EXPECT_EQ(22, cb.back());

    // Should now have 3 55 22
    EXPECT_EQ(3, cb[0]);
    EXPECT_EQ(55, cb[1]);
    EXPECT_EQ(22, cb[2]);
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
