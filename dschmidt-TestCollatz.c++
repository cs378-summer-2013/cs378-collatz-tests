// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*tp test the program:
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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read
    // ----


    //default test case
    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);}

//-------------------------
//My Created tests for read
//-------------------------        

	//big before small input
     void test_read_2 () 
     {
        std::istringstream r("142 69\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 142);
        CPPUNIT_ASSERT(j == 69);
     }

     //Big before Small
     void test_read_3 () 
     {
        std::istringstream r("15 3\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 15);
        CPPUNIT_ASSERT(j == 3);
     }


     //Same number
     void test_read_4 () 
     {
        std::istringstream r("1 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 1);
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

//-------------------------
//My created tests for eval
//-------------------------

    //base case of one and same number
    void test_eval_5 () 
    {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);
    }

    //large number range
    void test_eval_6 () 
    {
        const int v = collatz_eval(800000, 900000);
        CPPUNIT_ASSERT(v == 525);
    }

    //base case of one and same number
    void test_eval_7 () 
    {
        const int v = collatz_eval(225, 224);
        CPPUNIT_ASSERT(v == 53);
    }


    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}


//----------------------------
//user created tests for print
//----------------------------

    //random numerical input test
    void test_print_2 () 
    {
        std::ostringstream w;
        collatz_print(w, 210090, 476491, 449);//range from NFJones
        CPPUNIT_ASSERT(w.str() == "210090 476491 449\n");
    }

    //base case of 1
    void test_print_3 () 
    {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");
    }

    //big before small
    void test_print_4 () 
    {
        std::ostringstream w;
        collatz_print(w, 1090, 417, 179);//range from jkunze
        CPPUNIT_ASSERT(w.str() == "1090 417 179\n");
    }


    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}


//--------------------------
//my created tests for solve
//--------------------------
    //big before small test -one line
    void test_solve_2 () 
    {
        std::istringstream r("10 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n");
    }

    //3 random ranges
    void test_solve_3 () 
    {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");//ranges from jkinze gaurav taylor91
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
    }

    //9 inputs
    void test_solve_4 () 
    {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n1 10\n100 200\n201 210\n900 1000\n1 10\n100 200\n201 210\n900 1000\n");//ranges from jkinze gaurav taylor91
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n1 10 20\n100 200 125\n201 210 89\n900 1000 174\n1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
    }


    //--------------------
    //test_populate_helper
    //--------------------
   
    //base case test
    void test_populate_helper_1()
    {
	unsigned long l = 1;
	CPPUNIT_ASSERT(collatz_populate_helper(l) == 1);
    }
   
    //last index in cache
    void test_populate_helper_2()
    {
	unsigned long start = 999999;
        unsigned long result = collatz_populate_helper(start);
	CPPUNIT_ASSERT((int)result == 259);
    }

    //Index oustide of cache
    void test_populate_helper_3()
    {
	unsigned long l = 2094992;
	CPPUNIT_ASSERT((int)collatz_populate_helper(l) == 136);
    }

   

    //-------------------
    //test_populate_cache
    //-------------------

    void test_populate_cache()
    {

	CPPUNIT_ASSERT( c[1] == 1 && c[142243] == 189 && c[999999] == 259);
	
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
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


    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);

    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);

    CPPUNIT_TEST(test_populate_helper_1);
    CPPUNIT_TEST(test_populate_helper_2);
    CPPUNIT_TEST(test_populate_helper_3);
    
    CPPUNIT_TEST(test_populate_cache);

    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    collatz_populate_cache();
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}

