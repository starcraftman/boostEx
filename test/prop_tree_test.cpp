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
#include <exception> /* Top level exception header. */
//#include <stdexcept> /* Derived exception classes. */

/* STL Headers */
//#include <vector>
//#include <list>
//#include <deque>
//#include <stack>
//#include <queue>
//#include <priority_queue>
//#include <bitset>
#include <set> // multiset for multiple keys allowed.
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
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <gtest/gtest.h>

/******************* Constants/Macros *********************/
#define XML_DEBUG_ORIG "examples/property_tree/debug_settings.xml"
#define XML_DEBUG_NEW "debug_settings.xml"
#define JSON_DEBUG_NEW "debug_settings.json"

/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;
namespace pt = boost::property_tree;

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
struct DebugSettings {
    string m_file;
    int m_level;
    std::set<string> m_modules;
    void load(const string &filename);
    void save(const string &filename);
};

void DebugSettings::load(const string & filename) {
    pt::ptree pTree;
    pt::read_xml(filename, pTree);

    m_file = pTree.get<string>("debug.filename");
    m_level = pTree.get("debug.level", 0);

    for (auto value : pTree.get_child("debug.modules")) {
	m_modules.insert(value.second.data());
    }
}

void DebugSettings::save(const string & filename) {
    pt::ptree pTree;

    pTree.put("debug.filename", m_file);
    pTree.put("debug.level", m_level);

    for (auto module : m_modules) {
	pTree.add("debug.modules.module", module);
    }

    pt::write_xml(filename, pTree);
}

/****************** Global Functions **********************/
TEST(BoostPropTree, DebubPropXML) {
    DebugSettings ds;

    ASSERT_NO_THROW(ds.load(XML_DEBUG_ORIG));
    ASSERT_STREQ("debug.log", ds.m_file.c_str());
    ASSERT_EQ(2, ds.m_level);
    ASSERT_TRUE(ds.m_modules.count("Admin"));

    ASSERT_NO_THROW(ds.save(XML_DEBUG_NEW));
    ASSERT_TRUE(boost::filesystem::is_regular_file(XML_DEBUG_NEW));
    ASSERT_NO_THROW(std::remove(XML_DEBUG_NEW));
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
