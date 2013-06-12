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

    void test_read () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_2 () {
	std::istringstream r("");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	CPPUNIT_ASSERT(b == false);
	}

    void test_read_3 () {
	std::istringstream r("10000 10000");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 10000);
	CPPUNIT_ASSERT(j == 10000);
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

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 200, 300, 1);
        CPPUNIT_ASSERT(w.str() == "200 300 1\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 50, 50, 50);
        CPPUNIT_ASSERT(w.str() == "50 50 50\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_2 () {
        std::istringstream r("27 27\n6 6 9\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "27 27 111\n");}
    
    void test_solve_3 () {
        std::istringstream r("11 11\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "11 11 15\n");}
    

    // -----
    // find_collatz
    // -----

	void test_find_collatz_1 () {
		int i = 1;
		int v = find_collatz(i);
		CPPUNIT_ASSERT(v == 1);}

	void test_find_collatz_2 () {
		int i = 5;
		int v = find_collatz(i);
		CPPUNIT_ASSERT(v == 6);}

	void test_find_collatz_3 () {
		int i = 10;
		int v = find_collatz(i);
		CPPUNIT_ASSERT(v == 7);}

	void test_find_collatz_4 () {
		int i = 11;
		int v = find_collatz(i);
		CPPUNIT_ASSERT(v == 15);}
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_find_collatz_1);
    CPPUNIT_TEST(test_find_collatz_2);
    CPPUNIT_TEST(test_find_collatz_3);
    CPPUNIT_TEST(test_find_collatz_4);
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
