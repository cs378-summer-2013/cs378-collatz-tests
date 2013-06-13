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

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

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

    void test_read_01 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_02 () {
    	std::istringstream r("1 2\n3 4\n5 6\n");
    	int x1, x2, x3, x4, x5, x6;
    	const bool b1 = collatz_read(r, x1, x2);
    	const bool b2 = collatz_read(r, x3, x4);
    	const bool b3 = collatz_read(r, x5, x6);
    	CPPUNIT_ASSERT(b1);
    	CPPUNIT_ASSERT(b2);
    	CPPUNIT_ASSERT(b3);
    	CPPUNIT_ASSERT(x1 == 1);
    	CPPUNIT_ASSERT(x2 == 2);
    	CPPUNIT_ASSERT(x3 == 3);
    	CPPUNIT_ASSERT(x4 == 4);
    	CPPUNIT_ASSERT(x5 == 5);
    	CPPUNIT_ASSERT(x6 == 6);
    }

    void test_read_03 () {
    	std::istringstream r("12345 12345\n");
    	int x1, x2;
    	const bool b = collatz_read(r, x1, x2);
    	CPPUNIT_ASSERT(b);
    	CPPUNIT_ASSERT(x1 == 12345);
    	CPPUNIT_ASSERT(x2 == 12345);
    }

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);}

    void test_eval_05 () {
    	const int v = collatz_eval(1, 1);
    	CPPUNIT_ASSERT(v == 1);
    }

    void test_eval_06 () {
    	const int v = collatz_eval(10, 1);
    	CPPUNIT_ASSERT(v == 20);
    }

    void test_eval_07 () {
    	const int v = collatz_eval(10, 10);
    	CPPUNIT_ASSERT(v == 7);
    }

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_02 () {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");
    }

    void test_print_03 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n1 1 1\n");
    }

    void test_print_04 () {
        std::ostringstream w;
        std::ostringstream y;
        collatz_print(w, 1, 10, 20);
        collatz_print(y, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
        CPPUNIT_ASSERT(y.str() == "1 1 1\n");
    }

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_02 () {
        std::istringstream r("1 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");
    }

    void test_solve_03 () {
    	// TODO ask if this should return a blank string or a newline
    	//      for now, just assumming a blank string
        std::istringstream r("\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");
    }

    void test_solve_04 () {
    	// Make sure that they stay in the given order when given a larger int first
        std::istringstream r("10 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n");
    }

    void test_solve_05 () {
    	// Check for cached results
        std::istringstream r("1 10\n1 10\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n1 10 20\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_01);
    CPPUNIT_TEST(test_read_02);
    CPPUNIT_TEST(test_read_03);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_05);
    CPPUNIT_TEST(test_eval_06);
    CPPUNIT_TEST(test_eval_07);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_02);
    CPPUNIT_TEST(test_print_03);
    CPPUNIT_TEST(test_print_04);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_02);
    CPPUNIT_TEST(test_solve_03);
    CPPUNIT_TEST(test_solve_04);
    CPPUNIT_TEST(test_solve_05);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
