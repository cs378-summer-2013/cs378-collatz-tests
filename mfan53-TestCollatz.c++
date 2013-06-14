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

	void test_read2 () {
        std::istringstream r("53 216\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    53);
        CPPUNIT_ASSERT(j ==   216);}

	void test_read3 () {
        std::istringstream r("15 25\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    15);
        CPPUNIT_ASSERT(j ==   25);}

	void test_read4 () {
        std::istringstream r("300 900\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    300);
        CPPUNIT_ASSERT(j ==   900);}

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
	void test_eval_5 () {
        const int v = collatz_eval(53, 216);
        CPPUNIT_ASSERT(v == 125);}

	void test_eval_6() {
        const int v = collatz_eval(15, 25);
        CPPUNIT_ASSERT(v == 24);}

	void test_eval_7 () {
        const int v = collatz_eval(300, 900);
        CPPUNIT_ASSERT(v == 179);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
	void test_print2 () {
        std::ostringstream w;
        collatz_print(w, 53, 216, 125);
        CPPUNIT_ASSERT(w.str() == "53 216 125\n");}

	void test_print3 () {
        std::ostringstream w;
        collatz_print(w, 15, 25, 24);
        CPPUNIT_ASSERT(w.str() == "15 25 24\n");}

	void test_print4 () {
        std::ostringstream w;
        collatz_print(w, 300, 900, 179);
        CPPUNIT_ASSERT(w.str() == "300 900 179\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

	void test_solve2 () {
        std::istringstream r("1 10\n100 200\n300 900\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n300 900 179\n");}

	void test_solve3 () {
        std::istringstream r("1 10\n1 1\n15 25\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n1 1 1\n15 25 24\n");}

	void test_solve4 () {
        std::istringstream r("53 216\n300 900\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "53 216 125\n300 900 179\n900 1000 174\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_read2);
	CPPUNIT_TEST(test_read3);
	CPPUNIT_TEST(test_read4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
	CPPUNIT_TEST(test_eval_5);
	CPPUNIT_TEST(test_eval_6);
	CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print2);
	CPPUNIT_TEST(test_print3);
	CPPUNIT_TEST(test_print4);
    CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve2);
	CPPUNIT_TEST(test_solve3);
	CPPUNIT_TEST(test_solve4);
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
