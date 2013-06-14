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
    
    void test_read1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}
    void test_read2 () {
        std::istringstream r("20 30\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   20);
        CPPUNIT_ASSERT(j ==   30);}
    void test_read3 () {
        std::istringstream r("1001 1004\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   1001);
        CPPUNIT_ASSERT(j ==   1004);}
    void test_read4 () {
        std::istringstream r("14 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   14);
        CPPUNIT_ASSERT(j ==   10);}
    
    
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
        const int v = collatz_eval(10, 1);
        CPPUNIT_ASSERT(v == 20);}
    void test_eval_6 () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);}
    void test_eval_7 () {
        const int v = collatz_eval(10, 10);
        CPPUNIT_ASSERT(v == 7);}
    void test_eval_8 () {
        const int v = collatz_eval(100, 110);
        CPPUNIT_ASSERT(v == 114);}
    void test_eval_9 () {
        const int v = collatz_eval(35, 23);
        CPPUNIT_ASSERT(v == 112);}
    void test_eval_10 () {
        const int v = collatz_eval(47, 55);
        CPPUNIT_ASSERT(v == 113);}
    
    
    // -----
    // print
    // -----
    
    void test_print1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
    void test_print2 () {
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");}
    void test_print3 () {
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");}
    void test_print4 () {
        std::ostringstream w;
        collatz_print(w, 900, 100, 174);
        CPPUNIT_ASSERT(w.str() == "900 100 174\n");}
    
    
    // -----
    // solve
    // -----
    
    void test_solve1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
    void test_solve2 () {
        std::istringstream r("1 1\n10 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n10 1 20\n");}
    void test_solve3 () {
        std::istringstream r("100 110\n35 23\n47 55\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "100 110 114\n35 23 112\n47 55 113\n");}
    void test_solve4 () {
        std::istringstream r("13 19\n91 101\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "13 19 21\n91 101 119\n");}
    
    
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read1);
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
    CPPUNIT_TEST(test_eval_8);
    CPPUNIT_TEST(test_eval_9);
    CPPUNIT_TEST(test_eval_10);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_print4);
    CPPUNIT_TEST(test_solve1);
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
