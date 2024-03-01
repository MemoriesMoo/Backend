#pragma once

#include <stdio.h>
#include <assert.h>

typedef int data_type;
typedef struct SeqList
{
    data_type *data_; // 数据空间
    size_t size_;     // 数据个数
    size_t capacity_; // 数据容量
} SeqList;

// 初始化顺序表
void init(SeqList *psl);
// 销毁顺序表
void destory(SeqList *psl);
// 打印顺序表
void print(const SeqList *psl);

// 寻求特定值
int find(const SeqList *psl, data_type data);

// 特定位置插入
void insert(SeqList *psl, size_t pos, data_type data);

// 特定位置删除
void erase(SeqList *psl, size_t pos);

// 修改特定位置
void modify(SeqList *psl, size_t pos, data_type data);

// 检查容量
void check_capacity(SeqList *psl);

// 头插头删 尾插尾删
void push_back(SeqList *psl, data_type data);
void push_front(SeqList *psl, data_type data);
void pop_back(SeqList *psl);
void pop_front(SeqList *psl);
