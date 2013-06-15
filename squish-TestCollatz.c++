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

   // Check test_eval_1..4 with spans reversed
   void test_eval_5 () {
      const int v = collatz_eval(10, 1);
      CPPUNIT_ASSERT(v == 20);
   }

   void test_eval_6 () {
      const int v = collatz_eval(200, 100);
      CPPUNIT_ASSERT(v == 125);
   }

   void test_eval_7 () {
      const int v = collatz_eval(210, 201);
      CPPUNIT_ASSERT(v == 89);
   }

   void test_eval_8 () {
      const int v = collatz_eval(1000, 900);
      CPPUNIT_ASSERT(v == 174);
   }

   // Check identical endpoints
   void test_eval_9 () {
      const int v = collatz_eval(1, 1);
      CPPUNIT_ASSERT(v == 1);
   }

   void test_eval_10 () {
      const int v = collatz_eval(2, 2);
      CPPUNIT_ASSERT(v == 2);
   }

   void test_eval_11 () {
      const int v = collatz_eval(10, 10);
      CPPUNIT_ASSERT(v == 7);
   }

   // Check for overflow
   void test_eval_12 () {
      const int v = collatz_eval(113383, 113383);
      CPPUNIT_ASSERT(v == 248);
   }

   void test_eval_13 () {
      const int v = collatz_eval(270271, 270271);
      CPPUNIT_ASSERT(v == 407);
   }

   void test_eval_14 () {
      const int v = collatz_eval(626331, 626331);
      CPPUNIT_ASSERT(v == 509);
   }

   void test_eval_15 () {
      const int v = collatz_eval(1, 999999);
      CPPUNIT_ASSERT(v == 525);
   }

   void test_eval_16_new_max_1 () {
      int top;
      const int v = collatz_new_max(1, 999999, top);
      CPPUNIT_ASSERT(v == 525);
   }

   void test_eval_16_new_max_2 () {
      int top;
      int v = collatz_new_max(626331, 837798, top);
      CPPUNIT_ASSERT(v == 509);
   }

   void test_eval_16_new_max_3 () {
      int top;
      collatz_new_max(600000, 625000, top);
      CPPUNIT_ASSERT(top == 508);
   }

   void test_eval_16_new_max_4 () {
      int top;
      const int v = collatz_new_max(1, 1, top);
      CPPUNIT_ASSERT(v == 1);
   }

   void test_eval_16_new_max_5 () {
      int top;
      const int v = collatz_new_max(1, 2, top);
      CPPUNIT_ASSERT(v == 2);
   }   
   
   // Check that cache is storing values for starting values in span.
   void test_collatz_cache_read_1 () {
      collatz_cache_add(10);
      const int v = collatz_cache_read(10);
      CPPUNIT_ASSERT(v == 7);
   }

   void test_collatz_cache_read_2 () {
      collatz_cache_add(30);
      const int v = collatz_cache_read(30);
      CPPUNIT_ASSERT(v == 19);
   }

   void test_collatz_cache_read_3 () {
      collatz_cache_add(805);
      const int v = collatz_cache_read(805);
      CPPUNIT_ASSERT(v == 21);
   }

   void test_collatz_cache_init_1() {
      collatz_cache_init();
      //index 52527 is prepopulated in cache
      const int v = collatz_cache_read(52527);
      CPPUNIT_ASSERT(v == 340);
   }
  
   void test_collatz_cache_init_2() {
      collatz_cache_init();
      //index 327 is prepopulated in cache
      const int v = collatz_cache_read(327);
      CPPUNIT_ASSERT(v == 144);
   }

   void test_collatz_cache_init_3() {
      collatz_cache_init();
      //index 106239 is prepopulated in cache
      const int v = collatz_cache_read(106239);
      CPPUNIT_ASSERT(v == 354);
   }
    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    // -----
    // suite
    // -----
    CPPUNIT_TEST_SUITE(TestCollatz);

    CPPUNIT_TEST(test_read);

    CPPUNIT_TEST(test_collatz_cache_init_1);
    CPPUNIT_TEST(test_collatz_cache_init_2);
    CPPUNIT_TEST(test_collatz_cache_init_3);

    CPPUNIT_TEST(test_collatz_cache_read_1);
    CPPUNIT_TEST(test_collatz_cache_read_2);
    CPPUNIT_TEST(test_collatz_cache_read_3);

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
    CPPUNIT_TEST(test_eval_11);

    //Overflow
    
    CPPUNIT_TEST(test_eval_12);
    CPPUNIT_TEST(test_eval_13);
    CPPUNIT_TEST(test_eval_14);

    //Torture
    CPPUNIT_TEST(test_eval_15);
  
    //Newmax
    CPPUNIT_TEST(test_eval_16_new_max_1);
    CPPUNIT_TEST(test_eval_16_new_max_2);
    CPPUNIT_TEST(test_eval_16_new_max_3);
    CPPUNIT_TEST(test_eval_16_new_max_4);
    CPPUNIT_TEST(test_eval_16_new_max_5);
    
    CPPUNIT_TEST(test_print);
    
    CPPUNIT_TEST(test_solve);
    
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
    return 0;}
