// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program{
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
        std::istringstream r ("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
    }

    void test_read_large_32_bit () {
        std::istringstream r ("1 2147483647\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 2147483647);
    }

    void test_read_same_32_bit () {
        std::istringstream r ("78 78\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   78);
        CPPUNIT_ASSERT(j ==   78);
    }

    void test_read_same_large_32_bit () {
        std::istringstream r ("2147483647 2147483647\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 2147483647);
        CPPUNIT_ASSERT(j == 2147483647);
    }

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);
    }

    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);
    }

    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);
    }

    void test_eval_4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
    }

    void test_eval_5 () {
        const int v = collatz_eval(1, 1000);
        CPPUNIT_ASSERT(v == 179);
    }

    void test_eval_same_1 () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);
    }

    void test_eval_same_2 () {
        const int v = collatz_eval(5, 5);
        CPPUNIT_ASSERT(v == 6);
    }


    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
    }

    void test_print_large_32_bit () {
        std::ostringstream w;
        collatz_print(w, 1, 2147483647, 99999);
        CPPUNIT_ASSERT(w.str() == "1 2147483647 99999\n");
    }

    void test_print_same_32_bit () {
        std::ostringstream w;
        collatz_print(w, 78, 78, 78);
        CPPUNIT_ASSERT(w.str() == "78 78 78\n");
    }

    void test_print_same_large_32_bit () {
        std::ostringstream w;
        collatz_print(w, 2147483647, 2147483647, 2147483647);
        CPPUNIT_ASSERT(w.str() == "2147483647 2147483647 2147483647\n");
    }

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
    }

    void test_solve_02 () {
        std::istringstream r("1 1\n2 2\n8 8\n27 27\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n2 2 2\n8 8 4\n27 27 112\n");
    }

    void test_solve_03 () {
        std::istringstream r("1 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1000 179\n");
    }

    void test_solve_04 () {
        std::istringstream r("1 1000\n1 10000\n1 100\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1000 179\n1 10000 262\n1 100 119\n");
    }

    void test_solve_05 () {
        std::istringstream r("1 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");
    }

    // -----------------
    // test_cycle_length
    // -----------------

    void test_cycle_length_01 () {
        int value = collatz_cycle_length(1);
        CPPUNIT_ASSERT(value == 1);
    }

    void test_cycle_length_02 () {
        int value = collatz_cycle_length(2);
        CPPUNIT_ASSERT(value == 2);
    }

    void test_cycle_length_03 () {
        int value = collatz_cycle_length(8);
        CPPUNIT_ASSERT(value == 4);
    }

    void test_cycle_length_04 () {
        int value = collatz_cycle_length(27);
        CPPUNIT_ASSERT(value == 112);
    }

    void test_cycle_length_05 () {
        int value = collatz_cycle_length(5);
        CPPUNIT_ASSERT(value == 6);
    }

    void test_cycle_length_06 () {
        int value = collatz_cycle_length(6);
        CPPUNIT_ASSERT(value == 9);
    }



    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz); {
        CPPUNIT_TEST(test_read);
        CPPUNIT_TEST(test_read_large_32_bit);
        CPPUNIT_TEST(test_read_same_32_bit);
        CPPUNIT_TEST(test_read_same_large_32_bit);

        CPPUNIT_TEST(test_eval_1);
        CPPUNIT_TEST(test_eval_2);
        CPPUNIT_TEST(test_eval_3);
        CPPUNIT_TEST(test_eval_4);
        CPPUNIT_TEST(test_eval_5);
        CPPUNIT_TEST(test_eval_same_1);
        CPPUNIT_TEST(test_eval_same_2);

        CPPUNIT_TEST(test_print);
        CPPUNIT_TEST(test_print_large_32_bit);
        CPPUNIT_TEST(test_print_same_32_bit);
        CPPUNIT_TEST(test_print_same_large_32_bit);

        CPPUNIT_TEST(test_solve);
        CPPUNIT_TEST(test_solve_02);
        CPPUNIT_TEST(test_solve_03);
        CPPUNIT_TEST(test_solve_04);
        CPPUNIT_TEST(test_solve_05);

        CPPUNIT_TEST(test_cycle_length_01);
        CPPUNIT_TEST(test_cycle_length_02);
        CPPUNIT_TEST(test_cycle_length_03);
        CPPUNIT_TEST(test_cycle_length_04);
        CPPUNIT_TEST(test_cycle_length_05);
        CPPUNIT_TEST(test_cycle_length_06);
    } CPPUNIT_TEST_SUITE_END();
};

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
    return 0;
}
