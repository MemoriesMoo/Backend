#include <iostream>
#include <string>
#include <cstdio>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// 格式化线程id函数
std::string changeId(const pthread_t &threadId)
{
    char tid[64];
    snprintf(tid, sizeof(tid), "0x%x", pthread_self());
    return tid;
}

// 线程函数
void *threadFunc(void *arg)
{
    // 分离线程
    pthread_detach(pthread_self());
    int cnt = 5; // 计数器
    while (cnt)
    {
        std::string name = static_cast<const char *>(arg);
        std::cout << name << " is running..." << changeId(pthread_self()) << std::endl;
        cnt--;
        sleep(1);
    }

    // 结束线程
    pthread_exit(nullptr);
}

int main()
{
    pthread_t tid; // 线程id
    int ret;       // 函数返回值

    // 创建线程
    ret = pthread_create(&tid, nullptr, threadFunc, (void *)"new thread");
    if (ret != 0)
    {
        // 使用strerror输出错误信息
        fprintf(stderr, "pthread_create failed: %s\n", strerror(ret));
        return 1;
    }

    // 线程默认joinable，若在线程分离后join则出错
    // ret = pthread_join(tid, nullptr);
    // if (ret != 0)
    // {
    //     fprintf(stderr, "pthread_join failed: %s\n", strerror(ret));
    //     return 1;
    // }
}