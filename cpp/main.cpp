#include <iostream>
using namespace std;

#define COUT(...) cout << __VA_ARGS__

void test_VA_ARGS() {
	int a = 1;
	int b = 2;
	int c = 3;
	COUT(a << b << c << endl);
	COUT(a << b << c) << endl;
	COUT(a, b, c);
	cout << endl;
	// COUT(a, b, c) << endl; 
}

#include <iomanip>
void test_output_folating() {
	cout << fixed << 1.23456789 << endl;
	cout << fixed << setprecision(3) <<  1.23456789 << endl;
	cout << fixed << setprecision(7) <<  1.23456789 << endl;
	cout <<  1.23456789 << endl;
	cout << setprecision(5) << 4.786878 << endl;
	cout << setprecision(15) << 478 << endl;
	cout << fixed << setprecision(15) << 4.786878 << endl;
}


int main () {
	//test_VA_ARGS();
	test_output_folating();
	return 0;
}
