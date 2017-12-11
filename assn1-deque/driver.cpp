#include "deque.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

int main() {
	// Populate
	Deque<int> d;
	assert(d.size() == 0);
	for (int i = 0; i < 24; i += 2) {
		d.push_front(i);
		d.push_back(i + 1);
	}
	d.pop_back();
	assert(d.size() == 23);

	// Test push
	int nums[] = { 22,20,18,16,14,12,10,8,6,4,2,0,1,3,5,7,9,11,13,15,17,19,21 };

	// Test pop
	for (int i = 0; i < 6; ++i) {
		d.pop_back();
		d.pop_front();
	}
	assert(d.size() == 11);
	assert(equal(d.begin(), d.end(), nums + 6));

	// Test front, back, and at
	assert(d.front() == 10);
	d.front() = 100;
	assert(d.front() == 100);
	assert(d.at(0) == 100);
	assert(d.back() == 9);
	d.back() = 110;
	assert(d.back() == 110);
	assert(d.at(d.size() - 1) == 110);
	assert(d.at(1) == 8);
	d.at(1) = 80;
	assert(d.at(1) == 80);

	// Test boundaries and exceptions
	for (int i = 0; i < 100; ++i) {
		d.pop_back();
		d.pop_front();
	}
	assert(d.size() == 0);
	try {
		d.front();
		assert(false);
	}
	catch (logic_error&) {}
	try {
		d.back();
		assert(false);
	}
	catch (logic_error&) {}
	try {
		d.at(0);
		assert(false);
	}
	catch (logic_error&) {}

	// Now do strings
	Deque<string> d2;
	for (int i = 0; i < 24; i += 2) {
		d2.push_front(to_string(i));
		d2.push_back(to_string(i + 1));
	}
	d2.pop_back();
	assert(d2.size() == 23);

	// Test push
	string nums2[] = { "22","20","18","16","14","12","10","8","6","4","2","0",
		"1","3","5","7","9","11","13","15","17","19","21" };

	for (int i = 0; i < 6; ++i) {
		// Test pop
		d2.pop_back();
		d2.pop_front();
	}
	assert(d2.size() == 11);

	cout << "Tests passed\n";
	cin.get();
}
