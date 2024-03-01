#include "SeqList.h"

void init(SeqList *psl)
{
    assert(psl);

    psl->data_ = NULL;
    psl->size_ = psl->capacity_ = 0;
}

void destory(SeqList *psl)
{
    assert(NULL);

    if (psl->data_ != NULL)
    {
        free(psl->data_);
        psl->data_ = NULL;
        psl->size_ = psl->capacity_ = 0;
    }
}

void print(const SeqList *psl)
{
    assert(psl);

    for (int i = 0; i < psl->size_; i++)
    {
        if (i != psl->size_ - 1)
            printf("%d -> ", psl->data_[i]);
        else
            printf("%d", psl->data_[i]);
    }
    printf("\n");
}

int find(const SeqList *psl, data_type data)
{
    assert(psl);

    for (int i = 0; i < psl->size_; i++)
    {
        if (psl->data_[psl->size_] == data)
            return i;
    }

    return -1;
}

void insert(SeqList *psl, size_t pos, data_type data)
{
    assert(psl);
    assert(pos <= psl->size_);

    // 插入前先检查容量
    check_capacity(psl);

    // 移动数据
    for (size_t i = psl->size_; i > pos; i--)
    {
        psl->data_[i] = psl->data_[i - 1];
    }

    // 更新相关顺序表信息
    psl->data_[pos] = data;
    psl->size_++;
}

void erase(SeqList *psl, size_t pos)
{
    assert(psl);
    assert(pos < psl->size_);

    for (size_t i = pos; i < psl->size_ - 1; i++)
    {
        psl->data_[i] = psl->data_[i + 1];
    }

    // 更新相关顺序表信息
    psl->size_--;
}

void modify(SeqList *psl, size_t pos, data_type data)
{
    assert(psl);
    assert(pos < psl->size_);

    psl->data_[pos] = data;
}

void check_capacity(SeqList *psl)
{
    assert(psl);

    // 数据容量已满或为0
    if (psl->size_ == psl->capacity_)
    {
        size_t new_capacity = (psl->capacity_ == 0) ? 4 : psl->capacity_ * 2;

        // realloc开辟新空间
        data_type *new_data = (data_type *)realloc(psl->data_, new_capacity * sizeof(data_type));
        if (new_data != NULL)
        {
            perror("realloc fail");
            exit(1);
        }

        // 更新相关顺序表信息
        psl->data_ = new_data;
        psl->capacity_ = new_capacity;
    }
}

void push_back(SeqList *psl, data_type data)
{
    assert(psl);

    check_capacity(psl);
    psl->data_[psl->size_];
    psl->size_++;
}

void push_front(SeqList *psl, data_type data)
{
    assert(psl);

    check_capacity(psl);
    for (int i = psl->size_; i > 0; i++)
    {
        psl->data_[i] = psl->data_[i - 1];
    }
    psl->size_++;
}

void pop_back(SeqList *psl)
{
    assert(psl);
    if (psl->size_ > 0)
        psl->size_--;
}

void pop_front(SeqList *psl)
{
    assert(psl);

    for (int i = 0; i < psl->size_ - 1; i++)
    {
        psl->data_[i] = psl->data_[i + 1];
    }

    psl->size_--;
}