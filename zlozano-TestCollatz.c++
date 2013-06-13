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

    void test_read_2 ()      // Read multiple lines 
		{
		    std::istringstream r("2 4\n6 8\n10 12\n");
				int a, b, c, d, e, f;
				const bool g = collatz_read(r, a, b);
				const bool h = collatz_read(r, c, d);
				const bool i = collatz_read(r, e, f);
				CPPUNIT_ASSERT(g == true && h == true && i == true);
				CPPUNIT_ASSERT(a == 2);
				CPPUNIT_ASSERT(b == 4);
				CPPUNIT_ASSERT(c == 6);
				CPPUNIT_ASSERT(d == 8);
				CPPUNIT_ASSERT(e == 10);
				CPPUNIT_ASSERT(f == 12);
		}

		void test_read_3 ()      // Big to small read
		{
		    std::istringstream r("1000 30\n");
				int i, j;
				const bool b = collatz_read(r, i, j);
				CPPUNIT_ASSERT(b == true);
				CPPUNIT_ASSERT(i == 1000);
				CPPUNIT_ASSERT(j ==   30);
		}

		void test_read_4 ()      // Nill test
		{
		    std::istringstream r("");
				int i, j;
				const bool b = collatz_read(r, i ,j);
				CPPUNIT_ASSERT(b == false);
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

		void test_eval_5 ()      // DEcrementing range test
		{
		    const int v = collatz_eval(1000, 900);
				CPPUNIT_ASSERT(v == 174);
		}

		void test_eval_6 ()      // Equal endpoints
		{
		    const int v = collatz_eval(10, 10); 
				CPPUNIT_ASSERT(v == 7);
		}

		void test_eval_7 ()      // Input 1 test
		{
		    const int v = collatz_eval(1, 1);
				CPPUNIT_ASSERT(v == 1);
		}

		void test_eval_8 ()      // Enpoints test
		{
		    const int v = collatz_eval(5, 7);
				CPPUNIT_ASSERT(v == 17);
		}


		// ------------
		// cycle_length
		// ------------

		void test_cycle_length_1 ()
		{
		    int v = cycle_length(5);
				CPPUNIT_ASSERT(v == 6);
		}

		void test_cycle_length_2 ()
		{
		    int v = cycle_length(7);
				CPPUNIT_ASSERT(v == 17);
		}
		
		void test_cycle_length_3 ()
		{
		    int v = cycle_length(3);
				CPPUNIT_ASSERT(v == 8);
		}


    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

		void test_print_2 ()      
		{
        std::ostringstream w;
				collatz_print(w, 1, 1, 1);
				CPPUNIT_ASSERT(w.str() == "1 1 1\n");
		}

		void test_print_3 ()     
		{
        std::ostringstream w;
				collatz_print(w, 900, 1000, 174);
				CPPUNIT_ASSERT(w.str() == "900 1000 174\n");
		}


    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

		void test_solve_2 ()      // Max cycle length of 1 == 1
		{
        std::istringstream r("1 1\n");
				std::ostringstream w;
				collatz_solve(r, w);
				CPPUNIT_ASSERT(w.str() == "1 1 1\n");
		}
		
		void test_solve_3 ()      // Solve from hi to lo range
		{
        std::istringstream r("10 1\n");
				std::ostringstream w;
				collatz_solve(r, w);
				CPPUNIT_ASSERT(w.str() == "10 1 20\n");
		}
		
		void test_solve_4 ()      
		{
        std::istringstream r("66 542\n");
				std::ostringstream w;
				collatz_solve(r, w);
				CPPUNIT_ASSERT(w.str() == "66 542 144\n");
		}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
		CPPUNIT_TEST(test_cycle_length_1);
		CPPUNIT_TEST(test_cycle_length_2);
		CPPUNIT_TEST(test_cycle_length_3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
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
