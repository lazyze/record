/*
 * 进程相关的函数调用使用示例
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

int main() {
    pid_t childPid = fork();

    if (childPid == 0) {
        // 子进程执行的代码
        std::cout << "Child process executing..." << std::endl;
        exit(123);  // 子进程退出并返回退出状态
    } else if (childPid > 0) {
        // 父进程执行的代码
        int status;
        pid_t returnedPid = wait(&status);  // 等待子进程终止并获取退出状态
        if (returnedPid == childPid) {
            if (WIFEXITED(status)) {
                std::cout << "Child process exited with status: " << WEXITSTATUS(status) << std::endl;
            } else {
                std::cout << "Child process terminated abnormally." << std::endl;
            }
        } else {
            std::cout << "Error waiting for child process." << std::endl;
        }
    } else {
        // fork 失败
        std::cout << "Failed to create child process." << std::endl;
    }

    return 0;
}

