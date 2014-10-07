/**
 * Template C++ file.
 * Function with references to pointers: func(int *&ptr);
 */
/********************* Header Files ***********************/
/* C++ Headers */
#include <iostream> /* Input/output objects. */
//#include <fstream> /* File operations. */
//#include <sstream> /* String stream. */
#include <string> /* C++ String class. */
//#include <exception> /* Top level exception header. */
//#include <stdexcept> /* Some useful common exceptions */
//#include <new> /* Defines bad_malloc exception, new functions. */
//#include <memory> /* std smart pointers like unique_ptr */
//#include <typeinfo> /* Casting header. */
//#include <limits> /* Inspect properties, numeric_limits<int> iLimit; */
//#include <numeric> /* Math accumulators & other ops*/
//#include <functional> /* Function declarations & std::bind */

/* C++11 Only*/
//#include <chrono> /* std::chrono contains timing for threads */
//#include <initializer_list> /* Allows class to take list like {1,2} */
//#include <random> /* Random c++ version */
//#include <thread>
//#include <atomic>
//#include <condition_variable>
//#include <mutex>

/* STL Headers */
//#include <vector>
//#include <list>
//#include <deque>
//#include <stack>
//#include <queue>
//#include <priority_queue>
//#include <set> // multiset for multiple keys allowed.
//#include <map> // multimap for multiple keys allowed.
//#include <bitset>
#include <utility> // Has pair for map, std::swap
#include <algorithm>
//#include <iterator> // Contains back_inserter function and like.

/* C Headers */
//#include <cstdio>
//#include <cstring>
//#include <cstdlib> /* atof, rand, malloc... */
//#include <cstddef> /* size_t, NULL */
//#include <cstdarg> /* Variable argument functions */
//#include <cctype> /* Character check functions */
//#include <climits>
//#include <cassert>
//$include <cmath>
//$include <cstdint> /* C++11 only, standard u_int16 & such */

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <gtest/gtest.h>

/**************** Namespace Declarations ******************/
using std::cin;
using std::cout;
using std::endl;
using std::string;
namespace bg = boost::graph;

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

/***************** Constants & Macros *********************/


/****************** Class Definitions *********************/


/************** Global Vars & Functions *******************/
TEST(BoostGraph, CreateAdjList) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> Graph;

    enum { A, B, C, D, E, N };
    const int num_vertices = N;
    const char * name = "ABCDE";

    typedef std::pair<int, int> Edge;
    Edge edge_array[] = {
        Edge(A, B), Edge(A, D), Edge(C, A), Edge(D, C),
        Edge(C, E), Edge(B, D), Edge(D, E)
    };
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);

    Graph g(edge_array, edge_array + num_edges, num_vertices);

    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
    IndexMap index = boost::get(vertex_index, g);
}

/* Notes:
 * Force call to use another version of virtual function: baseP->Item_base::net_price(42);
 *
 */
