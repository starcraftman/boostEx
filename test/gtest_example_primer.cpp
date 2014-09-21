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
#include "gtest/gtest.h"

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
template <typename E>
class Queue {
public:
	Queue() {};
	void Enqueue(const E& element) {
		q.insert(q.begin(), element);
	};
	E* Dequeue() { // return null if empty
		if (q.empty()) {
			return NULL;
		} else {
			E* val = &q.back();
			q.pop_back();
			return val;
		}

	};
	size_t size() const {
		return q.size();
	};
private:
	std::vector<E> q;
};

class QueueTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		int val[] = {1, 2, 3};
		q1.Enqueue(val[0]);
		q2.Enqueue(val[1]);
		q2.Enqueue(val[2]);
	}

	virtual void TearDown() {
	}

	Queue<int> q0;
	Queue<int> q1;
	Queue<int> q2;
};

/****************** Global Functions **********************/
int fib(int n) {
	if (n < 0)
		return 0;
	if (n < 2)
		return n;

	int f_n2 = 0, f_n1 = 1, f_n = 0, t = 1;
	while(t++ != n) {
		f_n = f_n2 + f_n1;
		f_n2 = f_n1;
		f_n1 = f_n;
	}

	return f_n;
}

int factorial(int n) {
	if (n <= 1)
		return 1;

	int fact = 1;
	do {
		fact *= n;
	} while (n-- != 1);

	return fact;
}

void testAssert() {
	std::vector<int> v, v2;
	v.push_back(1);
	v2.push_back(1);

	ASSERT_EQ(v.size(), v2.size());

	for (std::vector<int>::size_type i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i], v2[i]) << "Vectors v & v2 differ at index " << i;
	}
}

TEST(FibTest, HandlesZeroInput) {
	EXPECT_EQ(0, fib(0));
}

TEST(FibTest, HandlesPositiveInput) {
	EXPECT_EQ(1, fib(1));
	EXPECT_EQ(1, fib(2));
	EXPECT_EQ(2, fib(3));
	EXPECT_EQ(21, fib(8));
}

TEST(FactTest, HandlesPositiveInput) {
	EXPECT_EQ(1, factorial(1));
	EXPECT_EQ(6, factorial(3));
	EXPECT_EQ(720, factorial(6));
	EXPECT_EQ(5040, factorial(7));
}

TEST_F(QueueTest, IsEmptyInitially) {
	EXPECT_EQ(0, q0.size());
}

TEST_F(QueueTest, DequeueWorks) {
	int *n = q0.Dequeue();
	EXPECT_EQ(NULL, n);

	n = q1.Dequeue();
	ASSERT_TRUE(n != NULL);
	EXPECT_EQ(1, *n);
	EXPECT_EQ(0, q1.size());

	n = q2.Dequeue();
	ASSERT_TRUE(n != NULL);
	EXPECT_EQ(2, *n);
	EXPECT_EQ(1, q2.size());
}

