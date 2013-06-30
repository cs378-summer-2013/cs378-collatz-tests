/*
 * TestPFD.c++
 * Created by Dan Jackson
 * June 29, 2013
 */


// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {

    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("10 1\n6 3 4 7 1");
		int map[101][101] = {{0}};
        int t = PFD_read(r, map);
        CPPUNIT_ASSERT(t == 10);
		CPPUNIT_ASSERT(map[0][0] == 10);
		CPPUNIT_ASSERT(map[6][0] == 3);
		CPPUNIT_ASSERT(map[6][4] == 1);
		CPPUNIT_ASSERT(map[6][7] == 1);
		CPPUNIT_ASSERT(map[6][1] == 1);}

    void test_read_2 () {
        std::istringstream r("42 5\n12 2 38 19\n4 1 9\n38 1 2\n29 1 1\n10 2 25 26");
		int map[101][101] = {{0}};
        int t = PFD_read(r, map);
        CPPUNIT_ASSERT(t == 42);
		CPPUNIT_ASSERT(map[0][0] == 42);
		CPPUNIT_ASSERT(map[12][38] 	== 1);
		CPPUNIT_ASSERT(map[12][19] 	== 1);	
		CPPUNIT_ASSERT(map[12][0]	== 2);
		CPPUNIT_ASSERT(map[4][9] 	== 1);	
		CPPUNIT_ASSERT(map[4][0]	== 1);
		CPPUNIT_ASSERT(map[38][2] 	== 1);	
		CPPUNIT_ASSERT(map[38][0]	== 1);
		CPPUNIT_ASSERT(map[29][1] 	== 1);	
		CPPUNIT_ASSERT(map[29][0]	== 1);
		CPPUNIT_ASSERT(map[10][25] 	== 1);	
		CPPUNIT_ASSERT(map[10][26] 	== 1);}
	
    void test_read_3 () {
        std::istringstream r("");
		int map[101][101] = {{0}};
        int t = PFD_read(r, map);
        CPPUNIT_ASSERT(t == 0);}


	// -----
	// print
	// -----
	void test_print_1 () {
		std::ostringstream w;
		std::vector<int> sol = {};
		sol.push_back(4);
		sol.push_back(2);
		sol.push_back(3);
		sol.push_back(1);
		PFD_print(w, sol, 4);
		CPPUNIT_ASSERT(w.str() == "4 2 3 1\n");}

	void test_print_2 () {
		std::ostringstream w;
		std::vector<int> sol = {};
		PFD_print(w, sol, 0);
		CPPUNIT_ASSERT(w.str() == "\n");}

	void test_print_3 () {
		std::ostringstream w;
		std::vector<int> sol = {};
		sol.push_back(45);
		sol.push_back(21);
		sol.push_back(8);
		sol.push_back(5);
		sol.push_back(34);
		sol.push_back(12);
		PFD_print(w, sol, 6);
		CPPUNIT_ASSERT(w.str() == "45 21 8 5 34 12\n");}

	
	// ----
	// pull
	// ----

	void test_pull_1() {
		int map[101][101] = {{0}};
		map[0][0] = 4;
		map[1][0] = 1;
		map[2][0] = 0;
		map[3][0] = 0;
		map[4][0] = 3;
		std::vector<int> sol;
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[0] == 2);
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[1] == 3);}

	void test_pull_2() {
		int map[101][101] = {{0}};
		map[0][0] = 4;
		map[1][0] = 1;
		map[2][0] = 0;
		map[3][0] = 0;
		map[4][0] = -1;
		std::vector<int> sol;
		sol.push_back(4);
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[0] == 4);
		CPPUNIT_ASSERT(sol[1] == 2);
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[2] == 3);}

	void test_pull_3() {
		int map [101][101] = {{0}};
		map[0][0] = 5;
		map[1][0] = 0;
		map[2][0] = 2;
		map[2][3] = 1;
		map[2][5] = 1;
		map[3][0] = 2;
		map[3][1] = 1;
		map[3][5] = 1;
		map[4][0] = 1;
		map[4][3] = 1;
		map[5][0] = 1;
		map[5][1] = 1;
		std::vector<int> sol;
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[0] == 1);
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[1] == 5);
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[2] == 3);
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[3] == 2);
		PFD_pull(map, sol);
		CPPUNIT_ASSERT(sol[4] == 4);}

	void test_solve_1() {
		std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
		std::ostringstream w;
		PFD_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 5 3 2 4\n");}

	void test_solve_2() {
		std::istringstream r("10 6\n5 5 3 4 4 6 6\n3 4 2 1 6 6\n2 1 7\n9 1 6\n8 2 1 10\n6 1 7");
		std::ostringstream w;
		PFD_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 4 7 2 6 3 5 9 10 8\n");}
		

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_pull_1);
	CPPUNIT_TEST(test_pull_2);
	CPPUNIT_TEST(test_pull_3);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
