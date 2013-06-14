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

#include <iostream> 	// cout, endl, ios_base
#include <sstream> 	// istringtstream, ostringstream
#include <string> 	// ==

#include "cppunit/extensions/HelperMacros.h" 	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" 		// TestFixture
#include "cppunit/TextTestRunner.h" 		// TextTestRunner

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
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);}

    // User Tests
    void test_read1 () {
        std::istringstream r("100 200\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 100);
        CPPUNIT_ASSERT(j == 200);}
  
    void test_read2 () {
        std::istringstream r("1000 50000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1000);
        CPPUNIT_ASSERT(j == 50000);}

    void test_read3 () {
        std::istringstream r("50001 777896\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 50001);
        CPPUNIT_ASSERT(j == 777896);}

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

    // User Tests
    void test_eval_5 () {
        const int v = collatz_eval(2429, 3496);
        CPPUNIT_ASSERT(v == 217);}
    
    void test_eval_6 () {
        const int v = collatz_eval(6519, 2895);
        CPPUNIT_ASSERT(v == 262);}

    void test_eval_7 () {
        const int v = collatz_eval(3830, 40652);
        CPPUNIT_ASSERT(v == 324);}


    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    // User Tests
    void test_print1 () {
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");}

    void test_print2 () {
        std::ostringstream w;
        collatz_print(w, 3830, 40652, 324);
        CPPUNIT_ASSERT(w.str() == "3830 40652 324\n");}

    void test_print3 () {
        std::ostringstream w;
        collatz_print(w, 6519, 2895, 262);
        CPPUNIT_ASSERT(w.str() == "6519 2895 262\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    // User Tests
    void test_solve1 () {
        std::istringstream r("3830 40652\n6519 2895\n2429 3496\n1185 38112\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "3830 40652 324\n6519 2895 262\n2429 3496 217\n1185 38112 324\n");}

    void test_solve2 () {
        std::istringstream r("400 23244\n8224 14575\n7395 47307\n9926 4367\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "400 23244 279\n8224 14575 276\n7395 47307 324\n9926 4367 262\n");}

    void test_solve3 () {
        std::istringstream r("8002 29\n7860 46420\n6009 91\n6691 22030\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "8002 29 262\n7860 46420 324\n6009 91 238\n6691 22030 279\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
