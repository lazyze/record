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

// #define TESTFUNC(NUM) \
//   int pri_##NUM##();  \
//   int pri_##NUM##() { \
//     int a = NUM;      \
//     return a;         \
//   }

// TESTFUNC(123);
// TESTFUNC(456);

// void test_defineFunc() {
//   cout << pri_123() << endl;
//   cout << pri_456() << endl;
// }

//测试内联汇编
namespace INLINE_ASSEMBLE {
typedef signed int s32_t;
typedef unsigned int u32_t;
//定义一个原子类型
typedef struct s_ATOMIC {
  volatile s32_t
      a_count;  //在变量前加上volatile，是为了禁止编译器优化，使其每次都从内存中加载变量
} atomic_t;
//原子读
static inline s32_t atomic_read(const atomic_t *v) {
  // x86平台取地址处是原子
  return (*(volatile u32_t *)&(v)->a_count);
}
//原子写
static inline void atomic_write(atomic_t *v, int i) {
  // x86平台把一个值写入一个地址处也是原子的
  v->a_count = i;
}
//原子加上一个整数
static inline void atomic_add(int i, atomic_t *v) {
  __asm__ __volatile__(
      "lock;"
      "addl %1,%0"
      : "+m"(v->a_count)
      : "ir"(i));
}
//原子减去一个整数
static inline void atomic_sub(int i, atomic_t *v) {
  __asm__ __volatile__(
      "lock;"
      "subl %1,%0"
      : "+m"(v->a_count)
      : "ir"(i));
}
//原子加1
static inline void atomic_inc(atomic_t *v) {
  __asm__ __volatile__(
      "lock;"
      "incl %0"
      : "+m"(v->a_count));
}
//原子减1
static inline void atomic_dec(atomic_t *v) {
  __asm__ __volatile__(
      "lock;"
      "decl %0"
      : "+m"(v->a_count));
}

void test_inline_assemble() {
  atomic_t a = {8};
  int i = 2;
  int j = 5;
  printf("原子变量的值为%d, 期待值为8\n", a.a_count);
  atomic_add(i, &a);
  printf("i的值为%d, 期待值为2\n", i);
  printf("原子变量的值为%d, 期待值为10\n", a.a_count);
  atomic_sub(j, &a);
  printf("原子变量的值为%d, 期待值为5\n", a.a_count);
}
}  // namespace INLINE_ASSEMBLE

namespace ENABLE_IF {
#define SFINAE_TYPE_SAME(type1, type2) \
  typename std::enable_if<std::is_same<type1, type2>::value>::type * = nullptr

template <typename T>
int FromString(const std::string &in, SFINAE_TYPE_SAME(T, int)) {
  return std::stoi(in);
}

template <typename T>
int64_t FromString(const std::string &in, SFINAE_TYPE_SAME(T, int64_t)) {
  return std::stoll(in);
}

void test() {
  std::string str("2147483647");
  std::string strl("4294967295");
  int num;
  int64_t numl;
  cout << "FromString结果为:"<< FromString<int>(str, &num) << "期望值:2147483647\n";
  cout << "FromString结果为:"<< FromString<int64_t>(strl, &numl) << "期望值:4294967295\n";
  // cout << "FromString结果为:"<< FromString<int>(strl, &numl) << "期望值:4294967295\n";
}
}  // namespace ENABLE_IF

int main() {
  // test_VA_ARGS();
  // test_output_folating();
  // test_dates_bytes();
  // test_strings();
  // INLINE_ASSEMBLE::test_inline_assemble();
  ENABLE_IF::test();
  return 0;
}
