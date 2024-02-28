#pragma once

#include <iostream>
#include <functional>
#include <pthread.h>
#include <string.h>

class Thread;

typedef std::function<void *(void *)> func_t;

// 上下文
class Contex
{
public:
    Contex() : this_(nullptr), args_(nullptr) {}
    ~Contex() {}

public:
    Thread *this_;
    void *args_;
};

// 线程类
class Thread
{
public:
    // 构造函数
    Thread(func_t func, void *args, int number)
        : func_(func), args_(args)
    {
        // 构建线程名称
        char nameBuffer[64]; 
        snprintf(nameBuffer, sizeof nameBuffer, "thread[%d]", number);
        name_ = nameBuffer;

        // 构建Contex对象
        tx_ = new Contex();
        tx_->this_ = this;
        tx_->args_ = args_;

        // 创建线程
        int ret = pthread_create(&tid_, nullptr, routine, tx_);
        if (ret != 0)
        {
            // 使用strerror输出错误信息
            fprintf(stderr, "pthread_create failed: %s\n", strerror(ret));
            exit(1);
        }
    }

    // 线程等待
    void join()
    {
        int ret = pthread_join(tid_, nullptr);
        if (ret != 0)
        {
            // 使用strerror输出错误信息
            fprintf(stderr, "pthread_join failed: %s\n", strerror(ret));
            exit(1);
        }
    }

    ~Thread()
    {
        delete tx_;
    }

private:
    std::string name_; // 线程名称
    pthread_t tid_;    // 线程id
    func_t func_;      // 执行函数
    void *args_;       // 函数参数
    Contex *tx_;       // 上下文

    // 执行辅助函数
    static void *routine(void *args)
    {
        Contex *tx = static_cast<Contex *>(args);
        return tx->this_->func_(tx->args_);
    }
};