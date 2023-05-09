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

  char str4[16] = "tcp://*:";
  char *pos = str4 + strlen(str4);
  uint32_t port = 8000;
  sprintf(pos, "%d", port);
  cout << "str4 = " << str4 << endl;
  cout << "str4的真实长度为" << strlen(str4) << endl;
  cout << "str4的数组长度为" << sizeof(str4) << endl;
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

// 测试内联汇编
namespace INLINE_ASSEMBLE {
typedef signed int s32_t;
typedef unsigned int u32_t;
// 定义一个原子类型
typedef struct s_ATOMIC {
  volatile s32_t
      a_count;  // 在变量前加上volatile，是为了禁止编译器优化，使其每次都从内存中加载变量
} atomic_t;
// 原子读
static inline s32_t atomic_read(const atomic_t *v) {
  // x86平台取地址处是原子
  return (*(volatile u32_t *)&(v)->a_count);
}
// 原子写
static inline void atomic_write(atomic_t *v, int i) {
  // x86平台把一个值写入一个地址处也是原子的
  v->a_count = i;
}
// 原子加上一个整数
static inline void atomic_add(int i, atomic_t *v) {
  __asm__ __volatile__(
      "lock;"
      "addl %1,%0"
      : "+m"(v->a_count)
      : "ir"(i));
}
// 原子减去一个整数
static inline void atomic_sub(int i, atomic_t *v) {
  __asm__ __volatile__(
      "lock;"
      "subl %1,%0"
      : "+m"(v->a_count)
      : "ir"(i));
}
// 原子加1
static inline void atomic_inc(atomic_t *v) {
  __asm__ __volatile__(
      "lock;"
      "incl %0"
      : "+m"(v->a_count));
}
// 原子减1
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
  cout << "FromString结果为:" << FromString<int>(str, &num)
       << "期望值:2147483647\n";
  cout << "FromString结果为:" << FromString<int64_t>(strl, &numl)
       << "期望值:4294967295\n";
  // cout << "FromString结果为:"<< FromString<int>(strl, &numl) <<
  // "期望值:4294967295\n";
}
}  // namespace ENABLE_IF

namespace CONST_PTR {
void test() {
  char test[10] = "hello";
  // char *const test;
  test[2] = 'x';
  printf("test[10] = %s\n", test);
  const char *buf = "helloworld";
  printf("buf = %s\n", buf);
  // buf[2] = 'x';
  buf = "another";
  // buf[12] = 'x';
  printf("buf = %s\n", buf);
}
}  // namespace CONST_PTR

#include <set>
#include <string>

#include "./toml11/toml.hpp"
#define IDENT "ident"
#define CONFPATH "/home/lize/ifads/test/iflog/conf/iflog_conf.toml"
namespace TOML {

std::set<std::string> InitLogFromConf(const char *confFileName) {
  std::set<std::string> ret;
  const auto data = toml::parse(confFileName);
  const auto map = toml::get<toml::table>(data);
  for (auto it = map.begin(); it != map.end(); it++) {
    if (toml::get<toml::table>(data).at(it->first).is_table()) {
      const auto name =
          toml::find_or<std::string>(toml::find(data, it->first), IDENT, "");
      if (!name.empty()) {
        string ident = name.substr(0, name.find_last_of('/'));
        ret.insert(ident);
      }
    }
  }
  return ret;
}

void test() {
  set<string> pos = InitLogFromConf(CONFPATH);
  for (auto it : pos) {
    cout << "日志文件位置：" << it << endl;
  }
}
}  // namespace TOML

#include <string.h>
#define LINE_SIZE (4096)
namespace TESTFILE {
int findSubstrPos(const char *dstStr, const char *subStr) {
  const char *ptr = strstr(dstStr, subStr);
  return ptr - dstStr;
}

int findLogDuration(FILE *fp) {
  int rt = 0;
  if (fp == NULL) return rt;
  char first_line[LINE_SIZE] = {};
  if (fgets(first_line, LINE_SIZE, fp) == NULL) return rt;
  char last_line[LINE_SIZE] = {};
  while (fgets(last_line, LINE_SIZE, fp))
    ;
  if (strlen(last_line) == 0) {
    return rt;
  }

  char first_time[LINE_SIZE] = {};
  memcpy(first_time, first_line, findSubstrPos(first_line, "  "));
  char last_time[LINE_SIZE] = {};
  memcpy(last_time, last_line, findSubstrPos(last_line, "  "));

  struct tm firstlogtime;
  struct tm lastlogtime;

  strptime(first_time, "%Y-%m-%d %H:%M:%S", &firstlogtime);
  strptime(last_time, "%Y-%m-%d %H:%M:%S", &lastlogtime);

  char firstlogtimestr[60];
  char lastlogtimestr[60];
  strftime(firstlogtimestr, 60, "第一条时间%Y-%m-%d %H:%M:%S", &firstlogtime);
  strftime(lastlogtimestr, 60, "最后一条时间%Y-%m-%d %H:%M:%S", &lastlogtime);
  cout << firstlogtimestr << endl;
  cout << lastlogtimestr << endl;

  time_t firstlogtimeSecond = mktime(&firstlogtime);
  time_t lastlogtimeSecond = mktime(&lastlogtime);
  cout << "相差秒数：" << lastlogtimeSecond - firstlogtimeSecond << endl;
  return rt;
}

void Func() {
  const char *path = "/home/lize/record/cpp/log/pnc-20230111_175634736.log.log";
  FILE *fp = fopen(path, "a+");
  char first_line[LINE_SIZE] = {};
  fgets(first_line, LINE_SIZE, fp);
  char last_line[LINE_SIZE] = {};
  int line_count = 1;
  while (fgets(last_line, LINE_SIZE, fp)) {
    line_count++;
    cout << "当前行数为：" << line_count << endl;
  }
  if (strlen(last_line) == 0) {
    memcpy(last_line, first_line, strlen(first_line));
  }
  cout << "总行数为：" << line_count << endl;
  cout << "第一行数据为: " << first_line << endl;
  cout << "最后一行数据为: " << last_line << endl;

  char first_time[LINE_SIZE] = {};
  memcpy(first_time, first_line, findSubstrPos(first_line, "  "));
  char last_time[LINE_SIZE] = {};
  memcpy(last_time, last_line, findSubstrPos(last_line, "  "));
  cout << "第一行时间数据为: " << first_time << endl;
  cout << "最后一行时间数据为: " << last_time << endl;

  char first_day[16] = {};
  memcpy(first_day, first_time, findSubstrPos(first_time, " "));
  char last_day[16] = {};
  memcpy(last_day, last_time, findSubstrPos(last_time, " "));
  cout << "第一行时间年月日数据为: " << first_day << endl;
  cout << "最后一行时间年月日数据为: " << last_day << endl;
  if (strcmp(first_day, last_day) != 0) {
    cout << "不属于同一天" << endl;
  }
  char first_min[16] = {};
  // memcpy(first_min, first_time + findSubstrPos(first_time, " ") + 1, 5);
  memcpy(first_min, strstr(first_time, " ") + 1, 5);
  char last_min[16] = {};
  // memcpy(last_min, last_time + findSubstrPos(last_time, " ") + 1, 5);
  memcpy(last_min, strstr(last_time, " ") + 1, 5);
  cout << "第一行时间分钟数据为: " << first_min << endl;
  cout << "最后一行时间分钟数据为: " << last_min << endl;
  char firstHourStr[4] = {};
  strncpy(firstHourStr, first_min, 2);
  char lastHourStr[4] = {};
  strncpy(lastHourStr, last_min, 2);

  char firstMinStr[4] = {};
  strncpy(firstMinStr, first_min + 3, 2);
  char lastMinStr[4] = {};
  strncpy(lastMinStr, last_min + 3, 2);
  int fisrtMin = atoi(firstHourStr) * 60 + atoi(firstMinStr);
  int lastMin = atoi(lastHourStr) * 60 + atoi(lastMinStr);
  cout << "第一行时间分钟数据为: " << fisrtMin << endl;
  cout << "最后一行时间分钟数据为: " << lastMin << endl;
  cout << "差距时间(分钟): " << lastMin - fisrtMin << endl;
}

void test() {
  const char *path = "/home/lize/record/cpp/log/pnc-20230111_175634736.log.log";
  FILE *fp = fopen(path, "a+");
  findLogDuration(fp);
}

}  // namespace TESTFILE

// 测试打开不存在的文件
namespace TESTOPEN {
int test(string &name) {
  fstream fs;
  fs.open(name.c_str(), std::fstream::in);
  if (fs.fail()) {
    std::cout << "Failed to open file!" << std::endl;
  } else {
    std::cout << "File opened successfully!" << std::endl;
  }
  pid_t pid = -1;
  fs >> pid;
  string proName;
  fs >> proName;
  char status;
  fs >> status;
  printf("open success, pid:%d name:%s status: %c\n", pid, proName.c_str(),
         status);
  return 0;
}
}  // namespace TESTOPEN

#include <cstdlib>
#include <ctime>
namespace RAND_NUMBER {
void test() {
  std::srand(std::time(0));  // 以当前时间为随机数生成器的种子
  int random_variable = std::rand() % 16777216;
  std::cout << "Random value on [0 " << RAND_MAX << "]: " << random_variable
            << '\n';
  std::cout << hex << setw(6) << setfill('0') << random_variable << std::endl;
  std::cout << random_variable << std::endl;
  char str[256];
  sprintf(str, "%016x\n", random_variable);
  std::cout << str << std::endl;
}
}  // namespace RAND_NUMBER

#include <dirent.h>

namespace FOLDER {
int test(string &path) {
  DIR *dir = NULL;
  dir = opendir(path.c_str());
  struct dirent *entry = NULL;

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 ||
        strcmp(entry->d_name, "..") == 0)  /// current dir OR parrent dir
    {
      continue;
    }
    char dir_pathname[5120] = {0};
    sprintf(dir_pathname, "%s/%s", path.c_str(), entry->d_name);
    // 4是目录 8是文件
    if (entry->d_type == 8) {
      printf("目前处理的文件为%s\n", dir_pathname);

    } else {
      printf("目前处理的文件夹为%s\n", dir_pathname);
      string folder = dir_pathname;
      test(folder);
    }
  }
  return 0;
}
}  // namespace FOLDER

#include <fstream>
#include <iostream>
namespace FILE_STRING {
int test(string &name) {
  ifstream ifile(name);
  //将文件读入到ostringstream对象buf中
  ostringstream buf;
  char ch;
  while(buf&&ifile.get(ch))
  buf.put(ch);
  string ret = buf.str();
  cout << "读取de字符串为:" << ret << ",长度为:" << ret.size() << endl;
  return 0;
}
int test2(string &name) {
  FILE *pFile = fopen(name.c_str(), "rb");
  // unsigned char buffer[1024] = "";
  char buffer[1024] = "";
  int len = 0;
  len = fread(buffer, 1, 1024, pFile);
  cout << "读取de字符串为:" << buffer << ",长度为:" << len << endl;
  return 0;
}
}  // namespace FILE_STRING

int main(int argc, char *argv[]) {
  // test_VA_ARGS();
  // test_output_folating();
  // test_dates_bytes();
  // test_strings();
  // INLINE_ASSEMBLE::test_inline_assemble();
  // ENABLE_IF::test();
  // CONST_PTR::test();
  // TOML::test();
  // TESTFILE::test();
  // string name("/proc/3497638/stat"); //success
  // string name("/proc/3497565438/stat");  // failed
  // TESTOPEN::test(name);
  // RAND_NUMBER::test();
  // string path = "../linux/objcopy/xavier/bin";
  // FOLDER::test(path);
  string name(argv[1]);
  FILE_STRING::test(name);
  FILE_STRING::test2(name);
  return 0;
}
