/*
 * @Author: lize GW00301491@ifyou.com
 * @Date: 2022-12-08 10:08:35
 * @LastEditors: lize GW00301491@ifyou.com
 * @LastEditTime: 2022-12-08 10:18:02
 * @FilePath: /test/home/lize/record/cpp/test/lockfreequeue.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef IFLOG_LOCKFREEQUEUE_H_
#define IFLOG_LOCKFREEQUEUE_H_

bool enqueue(char* buf, int len);
bool dequeue(char* buf, int len);

#endif