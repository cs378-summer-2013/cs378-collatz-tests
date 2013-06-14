// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lcppunit -ldl
    % valgrind TestCollatz >& TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <map>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_2 () {
        std::istringstream r("100 200\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   100);
        CPPUNIT_ASSERT(j ==   200);}

    void test_read_3 () {
        std::istringstream r("201 210\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   201);
        CPPUNIT_ASSERT(j ==   210);}

    void test_read_4 () {
        std::istringstream r("900 1000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   900);
        CPPUNIT_ASSERT(j ==  1000);}

    void test_read_5 () {
        std::istringstream r("50 30\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   50);
        CPPUNIT_ASSERT(j ==   30);}
    
    void test_read_6 () {
        std::istringstream r("71 1405\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   71);
        CPPUNIT_ASSERT(j ==   1405);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(9, 18);
        CPPUNIT_ASSERT_EQUAL(21, v);}

    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT_EQUAL(125, v);}

    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT_EQUAL(89, v);}

    void test_eval_4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT_EQUAL(174, v);}
	
	void test_eval_5 () {
		const int v = collatz_eval(10, 1);
		CPPUNIT_ASSERT_EQUAL(20, v);
	}

	void test_eval_6() {
		const int v = collatz_eval(1000, 900);
		CPPUNIT_ASSERT_EQUAL(174, v);
	}

	void test_eval_7() {
		const int v = collatz_eval(274102, 992204);
		CPPUNIT_ASSERT_EQUAL(525, v);
	}

	void test_cycleLength_1() {
		std::map <int, int> cache;
		const int v = cycleLength(9, cache);
		CPPUNIT_ASSERT_EQUAL(20, v);
	}

	void test_cycleLength_2() {
		std::map <int, int> cache;
		const int v = cycleLength(10, cache);
		CPPUNIT_ASSERT_EQUAL(7, v);
	}

	void test_cycleLength_3() {
		std::map <int, int> cache;
		const int v = cycleLength(396179, cache);
		CPPUNIT_ASSERT_EQUAL(69, v);	
	}

	void test_cycleLength_4() {
		std::map <int, int> cache;
		const int v = cycleLength(18, cache);
		CPPUNIT_ASSERT_EQUAL(21, v);
	}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");}

    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");}

    void test_print_5 () {
        std::ostringstream w;
        collatz_print(w, 13, 130, 210);
        CPPUNIT_ASSERT(w.str() == "13 130 210\n");}
    
    void test_print_6 () {
        std::ostringstream w;
        collatz_print(w, 61, 310, 240);
        CPPUNIT_ASSERT(w.str() == "61 310 240\n");}
    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_2 () {
        std::istringstream r("1 3\n1 5");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 3 8\n1 5 8\n");}

    void test_solve_3 () {
        std::istringstream r("1 10\n1 7");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n1 7 17\n");}

    void test_solve_4 () {
        std::istringstream r("495625 705494\n229705 378426\n608223 564520\n326615 702673\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "495625 705494 470\n229705 378426 443\n608223 564520 434\n326615 702673 470\n");}

    void test_solve_5 () {
        std::istringstream r("700138 983739\n61597 324117\n468919 436897\n519574 66398\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "700138 983739 525\n61597 324117 443\n468919 436897 444\n519574 66398 470\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_read_5);
    CPPUNIT_TEST(test_read_6);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
	CPPUNIT_TEST(test_eval_5);
	CPPUNIT_TEST(test_eval_6);
	CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_print_5);
    CPPUNIT_TEST(test_print_6);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);
	CPPUNIT_TEST(test_cycleLength_1);
	CPPUNIT_TEST(test_cycleLength_2);
	CPPUNIT_TEST(test_cycleLength_3);
	CPPUNIT_TEST(test_cycleLength_4);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () 
{
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
