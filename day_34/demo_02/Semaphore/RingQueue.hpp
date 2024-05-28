#pragma once
#include <semaphore.h>

// 单生产，单消费
// 多生产，多消费
// "321":
// 3: 三种关系
// a: 生产和消费互斥和同步
// b: 生产者之间:
// c: 消费者之间:
// 解决方案：加锁
// 1. 需要几把锁？2把
// 2. 如何加锁？

template <typename T>
class RingQueue
{
    void P(sem_t &sem)
    {
        sem_wait(&sem);
    }
    void V(sem_t &sem)
    {
        sem_post(&sem);
    }

    void Lock(pthread_mutex_t &_mutex)
    {
        pthread_mutex_lock(&_mutex);
    }

    void UnLock(pthread_mutex_t &_mutex)
    {
        pthread_mutex_unlock(&_mutex);
    }

public:
    RingQueue(int cap) : _cap(cap), _ring_queue(cap), _productor_index(0), _consumer_index(0)
    {
        sem_init(&_room_sem, 0, _cap); // 生产者 -- 开始空间是满的
        sem_init(&_data_sem, 0, 0);    // 消费者 -- 开始数据是没有的

        pthread_mutex_init(&_procductor_mutex, nullptr);
        pthread_mutex_init(&_consumer_mutex, nullptr);
    }
    void Enqueue(const T &in)
    {
        // 这里生产者和消费者存在的同步关系只在环形队列为满或者为空的时候，但是因为有信号量的保护，可以在这两种情况直接实现同步（因为信号量为0的时候会等待）
        P(_room_sem);
        // 预定机制，此时必定有一个空间可以放数据
        Lock(_procductor_mutex);
        _ring_queue[_productor_index++] = in;
        _productor_index %= _cap;
        UnLock(_procductor_mutex);
        V(_data_sem); // 生产好了一个数据
    }
    void Pop(T *out)
    {
        P(_data_sem);
        // 预定机制，此时必定有一个数据可以消费
        Lock(_consumer_mutex);
        *out = _ring_queue[_consumer_index++]; // 覆盖式的使用环形队列
        _consumer_index %= _cap;
        UnLock(_consumer_mutex);
        V(_room_sem); // 释放一个空间
    }
    ~RingQueue()
    {
        sem_destroy(&_room_sem);
        sem_destroy(&_data_sem);

        pthread_mutex_destroy(&_procductor_mutex);
        pthread_mutex_destroy(&_consumer_mutex);
    }

private:
    vector<T> _ring_queue;
    int _cap; // 容量上限

    int _productor_index; // 生产者的下标
    int _consumer_index;  // 消费者的下标

    // 信号量
    sem_t _room_sem; // 生产者关心
    sem_t _data_sem; // 消费者关心

    // 使用锁，解决多生产者多消费者的互斥访问
    pthread_mutex_t _procductor_mutex;
    pthread_mutex_t _consumer_mutex;
};