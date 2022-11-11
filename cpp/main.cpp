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
  cout << fixed << setprecision(3) << 1.23456789 << endl;
  cout << fixed << setprecision(7) << 1.23456789 << endl;
  cout << 1.23456789 << endl;
  cout << setprecision(5) << 4.786878 << endl;
  cout << setprecision(15) << 478 << endl;
  cout << fixed << setprecision(15) << 4.786878 << endl;
}

#define SIZEOF(type) \
  { cout << "sizeof(" #type ") = " << sizeof(type) << endl; }
void test_dates_bytes() {
  SIZEOF(int);
  SIZEOF(short);
  SIZEOF(long);
  SIZEOF(long long);
  // SIZEOF();
  // SIZEOF();
  // SIZEOF();
  // SIZEOF();
  // SIZEOF();
}

#include <string.h>
void test_strings() {
  char str[1024] =
      "0123456789"
      "0123456789"
      "0123456789"
      "0123456789"
      "0123456789";
  char str1[1024] =
      "0123456789\
                      0123456789\
                        0123456789\
                          0123456789\
                            0123456789";

  char str2[1024] =
      "0123456789 \
                      0123456789 \
                        0123456789 \
                          0123456789 \
                            0123456789";
  cout << "strlen(str)" << strlen(str) << endl;
  cout << "strlen(str1)" << strlen(str1) << endl;
  cout << "strlen(str2)" << strlen(str2) << endl;

  char str3[1024] = "isokisok";
  int i = 0;
  for (; i < 3; i++) {
    str3[i] = 'a' + i % 26;
  }
  str3[i] = 0;
  cout << "strlen(str3)" << strlen(str3) << endl;
}

#define TESTFUNC(NUM) \
  int pri_##NUM##();      \
  int pri_##NUM##() {     \
    int a = NUM;      \
    return a;         \
  }

TESTFUNC(123);
TESTFUNC(456);

void test_defineFunc() {
  cout << pri_123() << endl;
  cout << pri_456() << endl;
}

int main() {
  // test_VA_ARGS();
  // test_output_folating();
  // test_dates_bytes();
  test_strings();
  return 0;
}
