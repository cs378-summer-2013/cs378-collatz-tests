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

    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}
    
    void test_read_2 () {
        std::istringstream r("1 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 1000000);}

    // ----
    // lazy cache lookup
    // ----
    
    void test_lazy_cache_1 () {
        const int len = collatz_lazy_cache(1);
        CPPUNIT_ASSERT(len == 1);
    }

    void test_lazy_cache_2 () {
        const int len = collatz_lazy_cache(99);
        CPPUNIT_ASSERT(len == 26);
    }
    
    // ----
    // compute length of collatz sequence
    // ----

    void test_compute_collatz_1 () {
        const int len = collatz_compute(1);
        CPPUNIT_ASSERT(len == 1);
    }

    void test_compute_collatz_2 () {
        const int len = collatz_compute(2);
        CPPUNIT_ASSERT(len == 2);
    }

    void test_compute_collatz_3 () {
        const int len = collatz_compute(99);
        CPPUNIT_ASSERT(len == 26);
    }

    void test_compute_collatz_4 () {
        const int len = collatz_compute(929679);
        CPPUNIT_ASSERT(len == 171);
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
    
    void test_eval_5 () {
        const int v = collatz_eval(1,1);
        CPPUNIT_ASSERT(v==1);}

    void test_eval_6 () {
        const int v = collatz_eval(2,2);
        CPPUNIT_ASSERT(v==2);}

    void test_eval_7 () {
        const int v = collatz_eval(744,397);
        CPPUNIT_ASSERT(v==171);}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
    
    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 1, 1000000, 20);
        CPPUNIT_ASSERT(w.str() == "1 1000000 20\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
    
    void test_solve_2 () {
        std::istringstream r("2 2\n1 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2 2 2\n1 1 1\n");}
    
    void test_solve_3 () {
        std::istringstream r("397 744\n514 723\n173 199\n66 542\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "397 744 171\n514 723 171\n173 199 120\n66 542 144\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_lazy_cache_1);
    CPPUNIT_TEST(test_lazy_cache_2);
    CPPUNIT_TEST(test_compute_collatz_1);
    CPPUNIT_TEST(test_compute_collatz_2);
    CPPUNIT_TEST(test_compute_collatz_3);
    CPPUNIT_TEST(test_compute_collatz_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
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
