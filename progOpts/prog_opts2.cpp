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
#include <iterator> // Contains back_inserter function and like.

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
#include <boost/program_options.hpp>
#include <gtest/gtest.h>

/******************* Constants/Macros *********************/


/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;
namespace po = boost::program_options;

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
template<class T>
std::ostream & operator<<(std::ostream & os, const std::vector<T> & v) {
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

int main(int argc, char *argv[]) {
    try {
        int opt;
        int portnum;
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("compression", po::value<int>(), "set compression level")
            ("optimization level", po::value<int>(&opt)->default_value(10),
                 "optimization level")
            ("verbose,v", po::value<int>()->implicit_value(1),
                "enable verbosity (optionally specify level)")
            ("listen,l", po::value<int>(&portnum)->implicit_value(1001)
                ->default_value(0, "no"), "listen on a port")
            ("include-path,I", po::value< std::vector<string> >(), "include path")
            ("input-file", po::value< std::vector<string> >(), "input file")
        ;

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).
                  options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << endl;
            return 1;
        }
        if (vm.count("compression")) {
            cout << "Compression level was set to: " << vm["compression"].as<int>() << endl;
        } else {
            cout << "Compression level was not set." << endl;
        }
        if (vm.count("include-path")) {
            cout << "Include paths are: "
                << vm["include-path"].as< std::vector<string> >() << endl;
        }
        if (vm.count("input-file")) {
            cout << "Input files are: "
                << vm["input-file"].as< std::vector<string> >() << endl;
        }
        if (vm.count("verbose")) {
            cout << "Verbosity enabled. Level is " << vm["verbose"].as<int>() << endl;
        }

        cout << "Optimization level is " << opt << endl;
        cout << "Listen port is " << portnum << endl;
    }
    catch(std::exception& e) {
        std::cerr << "error: " << e.what() << endl;
        return 1;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!" << endl;
    }

    return 0;
}


/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
