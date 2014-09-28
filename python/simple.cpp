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
#include <boost/python.hpp>

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
class World {
public:
    World(string msg) : msg(msg) {}
    inline void set(string msg) { this->msg = msg; }
    inline string greet() { return msg; }
private:
    string msg;
};

class Var {
public:
    Var(std::string name) : name(name), val(0) {}
    string const name;
    float val;
};

class ClassProp {
public:
    ClassProp() : val(0) {};
    float get() const { return val; }
    void setV(float value) { val = value; }
private:
    float val;
};

/****************** Global Functions **********************/
char const * greet() {
    return "hello, world";
}

BOOST_PYTHON_MODULE(libBoost) {
    boost::python::def("greet", greet);

    boost::python::class_<World>("World", boost::python::init<string>())
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;

    boost::python::class_<Var>("Var", boost::python::init<string>()) 
        .def_readonly("name", &Var::name)
        .def_readwrite("value", &Var::val)
    ;

    boost::python::class_<ClassProp>("ClassProp")
        .add_property("rovalue", &ClassProp::get)
        .add_property("value", &ClassProp::get, &ClassProp::setV)
    ;
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
