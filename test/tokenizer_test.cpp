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
#include <boost/date_time.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
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
typedef std::vector<string> vs_t;;

/****************** Class Definitions *********************/


/****************** Global Functions **********************/
void assertEquality(vs_t expect, vs_t actual) {
    vs_t::const_iterator itrE = expect.begin();
    for (vs_t::const_iterator itrA = actual.begin(); itrA != actual.end(); ++itrA, ++itrE) {
        ASSERT_STREQ(itrE->c_str(), itrA->c_str());
    }
}

TEST(BoostTokenizer, SimpleTokenizer) {
    vs_t tokensActual, tokensExpect = {"This", "is", "a", "test" };
    string s = "This is,  a test";

    boost::tokenizer<> tokens(s);
    for (auto tok : tokens) {
        tokensActual.push_back(tok);
    }

    assertEquality(tokensExpect, tokensActual);
}

TEST(BoostTokenizer, CSVTokenizer) {
    vs_t tokensActual, tokensExpect = {"Field 1",
        "putting quotes around fields, allows commas", "Field 3"};
    string s = "Field 1,\"putting quotes around fields, allows commas\",Field 3";

    boost::tokenizer<boost::escaped_list_separator<char> > tokens(s);
    for (auto tok : tokens) {
        tokensActual.push_back(tok);
    }

    assertEquality(tokensExpect, tokensActual);
}

TEST(BoostTokenizer, OffsetTokenizer) {
    vs_t tokensActual, tokensExpect = {"12", "25", "2001"};
    string s = "12252001";
    int offsets[] = {2, 2, 4};

    boost::offset_separator offSeps(offsets, offsets+3);
    boost::tokenizer<boost::offset_separator> tokens(s, offSeps);

    for (auto tok : tokens) {
        tokensActual.push_back(tok);
    }

    assertEquality(tokensExpect, tokensActual);
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
