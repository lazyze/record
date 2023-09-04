/*
 * 进程相关的函数调用使用示例

正常运行结束会返回0


子进程的退出状态码通常会被截断为一个8位整数


在外部kill掉子进程的情况：
Child process terminated abnormally.
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <thread>

void waitChildProcess() {
  int status;
  pid_t returnedPid = wait(&status);  // 等待子进程终止并获取退出状态
  if (WIFEXITED(status)) {
    std::cout << "Child process exited with status: " << WEXITSTATUS(status)
              << std::endl;
  } else {
    std::cout << "Child process terminated abnormally." << std::endl;
  }
}

int main() {
    std::cout << "sizeof(int): " << sizeof(int) << std::endl;
  pid_t childPid = fork();

  if (childPid == 0) {
    // 子进程执行的代码
    std::cout << "Child process executing..." << std::endl;
    for (int i = 0; i < 10; i++) {
      std::cout << "Child process, i = " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // exit(123);  // 子进程退出并返回退出状态
    exit(257);  // 子进程退出并返回退出状态
  } else if (childPid > 0) {
    std::cout << "child pid: " << childPid << std::endl;
    // 父进程执行的代码
    std::thread waitThread(
        waitChildProcess);  // 创建新线程调用 waitChildProcess 函数

    // 等待一段时间，以便观察输出
    for (int i = 0; i < 300; i++) {
      std::cout << "main process, i = " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::this_thread::sleep_for(std::chrono::seconds(60));

  } else {
    // fork 失败
    std::cout << "Failed to create child process." << std::endl;
  }

  return 0;
}
