// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2011
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestCollatz.c++ -o TestCollatz.c++.app
    % valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
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

    /**
	 * Test reading an basic line
	 */
    void test_read_basic () {
        std::istringstream r("1 10\n");
        int i = 0;
        int j = 0;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
	}

    /**
	 * Test reading an empty line 
	 */
    void test_read_zero () {
        std::istringstream r("");
        int i = 0;
        int j = 0;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
        CPPUNIT_ASSERT(i ==   0);
        CPPUNIT_ASSERT(j ==   0);
	}

    /**
	 * Test reading a line with extra spaces
	 */
    void test_read_spaces () {
        std::istringstream r(" 1 1000 \n");
        int i = 0;
        int j = 0;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   1);
        CPPUNIT_ASSERT(j ==   1000);
	}

    /**
	 * Test reading a line with three numbers
	 */
    void test_read_incorrect_format () {
        std::istringstream r("13 14 15\n");
        int i = 0;
        int j = 0;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   13);
        CPPUNIT_ASSERT(j ==   14);
	}

    /**
	 * Test sphere collatz example 1
	 */
    void test_eval_collatz1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);
	}

	/**
	 * Test sphere collatz example 2
	 */
    void test_eval_collatz2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);
	}

	/**
	 * Test sphere collatz example 3
	 */
    void test_eval_collatz3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);
	}

	/**
	 * Test sphere collatz example 4
	 */
    void test_eval_collatz4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
	}

	/**
	 * Test evaluating where integers i and j are equal
	 */
    void test_eval_equal () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);}

	/**
	 * Test evaluating where integer i is greater than j
	 */
    void test_eval_medium () {
        const int v = collatz_eval(1000, 900);
        CPPUNIT_ASSERT(v == 174);}

	/**
	 * Test evaluating where integers i and j are equal 
	 */
    void test_eval_large () {
        const int v = collatz_eval(1000000, 1000000);
        CPPUNIT_ASSERT(v == 153);}


	/**
	 * Test the cycle function on integer 10
	 */
    void test_cycle_10 () {
        const int v = cycle(10);
        CPPUNIT_ASSERT(v == 7);
	}

	/**
	 * Test the cycle function on integer 20
	 */
    void test_cycle_20 () {
        const int v = cycle(20);
        CPPUNIT_ASSERT(v == 8);
	}

	/**
	 * Test the cycle function on integer 1
	 */
    void test_cycle_one() {
        const int v = cycle(1);
        CPPUNIT_ASSERT(v == 1);
	}

    // -----
    // print
    // -----

    void test_print_example () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_one () {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}

    void test_print_medium () {
        std::ostringstream w;
        collatz_print(w, 10, 10, 7);
        CPPUNIT_ASSERT(w.str() == "10 10 7\n");}

    void test_print_large () {
        std::ostringstream w;
        collatz_print(w, 1000, 900, 174);
        CPPUNIT_ASSERT(w.str() == "1000 900 174\n");}

    // -----
    // solve
    // -----

    void test_solve_example () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_large () {
        std::istringstream r("1 1\n1000 900\n1000000 1000000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n1000 900 174\n1000000 1000000 153\n");}

    void test_solve_medium () {
        std::istringstream r("57 96\n13 113\n10 100\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "57 96 116\n13 113 119\n10 100 119\n");}

    void test_solve_random () {
        std::istringstream r("10 100\n50 100\n57967 60000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 100 119\n50 100 119\n57967 60000 304\n");}
		
	// ----
	// init_cache
	// ----

	void testCache_six() {
		int cache_size = 6;
		int main_cache [6] = { 0 };
		init_cache(main_cache, cache_size);

		int test [6] = {0, 1, 2, 8, 3, 6};

		for(int i = 0; i < cache_size; i++) {
			if(main_cache[i] != test[i]) {
				CPPUNIT_ASSERT(false);
			}
		}
		CPPUNIT_ASSERT(true);
	}

	void testCache_eleven() {
		int cache_size = 11;
		int main_cache [11] = { 0 };
		init_cache(main_cache, cache_size);

		int test [11] = {0, 1, 2, 8, 3, 6, 9, 17, 4, 20, 7};

		for(int i = 0; i < cache_size; i++) {
			if(main_cache[i] != test[i]) {
				CPPUNIT_ASSERT(false);
			}
		}
		CPPUNIT_ASSERT(true);
	}

	void testCache_two() {
		int cache_size = 2;
		int main_cache [2] = { 0 };
		init_cache(main_cache, cache_size);

		int test [2] = {0, 1};

		for(int i = 0; i < cache_size; i++) {
			if(main_cache[i] != test[i]) {
				CPPUNIT_ASSERT(false);
			}
		}
		CPPUNIT_ASSERT(true);
	}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_basic);
    CPPUNIT_TEST(test_read_zero);
    CPPUNIT_TEST(test_read_spaces);
    CPPUNIT_TEST(test_read_incorrect_format);
    CPPUNIT_TEST(test_eval_collatz1);
    CPPUNIT_TEST(test_eval_collatz2);
    CPPUNIT_TEST(test_eval_collatz3);
    CPPUNIT_TEST(test_eval_collatz4);
    CPPUNIT_TEST(test_eval_equal);
    CPPUNIT_TEST(test_eval_medium);
    CPPUNIT_TEST(test_eval_large);
    CPPUNIT_TEST(test_cycle_10);
    CPPUNIT_TEST(test_cycle_20);
    CPPUNIT_TEST(test_cycle_one);
    CPPUNIT_TEST(test_print_example);
    CPPUNIT_TEST(test_print_one);
    CPPUNIT_TEST(test_print_medium);
    CPPUNIT_TEST(test_print_large);
    CPPUNIT_TEST(test_solve_example);
    CPPUNIT_TEST(test_solve_large);
    CPPUNIT_TEST(test_solve_medium);
    CPPUNIT_TEST(test_solve_random);
	CPPUNIT_TEST(testCache_six);
    CPPUNIT_TEST(testCache_eleven);
    CPPUNIT_TEST(testCache_two);
    CPPUNIT_TEST_SUITE_END();
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
