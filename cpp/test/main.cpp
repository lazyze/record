/*
 * @Author: lize GW00301491@ifyou.com
 * @Date: 2022-12-06 16:14:40
 * @LastEditors: lize GW00301491@ifyou.com
 * @LastEditTime: 2023-02-02 11:24:16
 * @FilePath: /record/cpp/test/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <unistd.h>

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "./concurrentqueue.h"
#include "./blockingconcurrentqueue.h"

using namespace std;
int num = 0;
pthread_mutex_t g_mutex;
uint64_t max_duration = 0;

int main() {
  cout << "main start..." << endl;
  pthread_mutex_init(&g_mutex, NULL);
  std::thread threads[20];
  char buf[256] =
      "hello12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567"
      "890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  // 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
  string data(buf);
  // moodycamel::ConcurrentQueue<string> ccq;
  moodycamel::BlockingConcurrentQueue<string> ccq;
  for (int i = 0; i != 10; ++i) {
    threads[i] = std::thread(
        [&](int i) {
          int count;
          while (1) {
            std::this_thread::sleep_for(std::chrono::microseconds(10));
            //开始打点
            struct timespec begin;
            struct timespec end;
            clock_gettime(CLOCK_REALTIME, &begin);

            //生产数据
            //  pthread_mutex_lock(&g_mutex);
            //         num++;
            //         num %= 100000;
            // pthread_mutex_unlock(&g_mutex);
            // count = num;
            // string tmp = data + to_string(count);
            ccq.enqueue(data);

            //结束打点
            clock_gettime(CLOCK_REALTIME, &end);
            uint64_t every_dur = end.tv_sec * 1000000000 + end.tv_nsec - (begin.tv_sec * 1000000000 + begin.tv_nsec);
            //   sleep(5);
              printf("生产数据消耗时间max_duration增大为%lums\n", max_duration );
            // if(max_duration / 1000 > 200) printf("大于200ns\n");
            if (every_dur > max_duration) {
              max_duration = every_dur;
              printf("生产数据消耗时间max_duration增大为%luus, %luns %lums\n", max_duration, max_duration / 1000,
                     max_duration / 1000000);
              sleep(5);
            }
          }
        },
        i);
  }

  // Consumers
  for (int i = 10; i != 15; ++i) {
    threads[i] = std::thread([&]() {
      string item;
      int i = 1;
      while (1) {
        // ccq.try_dequeue(item);
        ccq.wait_dequeue(item);
        i++;
        if (i == 10000000) {
          // sleep(10);
          // cout << item << endl;
          i %= 10000000;
        }
      }
    });
  }

  // Wait for all threads
  for (int i = 0; i != 11; ++i) {
    threads[i].join();
  }

  return 0;
}
