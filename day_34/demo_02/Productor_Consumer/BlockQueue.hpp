#ifndef __BLOCK_QUEUE_HPP__
#define __BLOCK_QUEUE_HPP__
#include <queue>

template <class T>
class BlockQueue
{
private:
    bool IsFull()
    {
        return _block_queue.size() == _cap;
    }
    bool IsEmpty()
    {
        return _block_queue.size() == 0;
    }

public:
    BlockQueue(int cap) : _cap(cap)
    {
        // 一开始有0个生产者等待，0个消费者等待
        _product_wait_num = 0;
        _consume_wait_num = 0;
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_product_cond, nullptr);
        pthread_cond_init(&_consume_cond, nullptr);
    }

    void Enqueue(const T &in)
    { // 生产者
        pthread_mutex_lock(&_mutex);

        // 不能用if，保证代码的健壮性
        // 考虑一种情况 ：只有1个生产者，有5个消费者

        // 此时没有数据，消费者先启动，那么5个消费者在条件变量下等待。
        // 然后生产者生产了1个数据，然后生产者broadcast唤醒了所有消费者
        // 此时有一个消费者竞争mutex锁成功，其他4个消费者在mutex锁下等待（所有消费者线程已唤醒，不再在条件变量下等待）
        // 那么当这个消费者消费完释放mutex锁后，这个等待的4个消费者中的一个消费者拿到锁，直接向下执行了！而此时队列已经没有数据了！那么就会出错。
        while (IsFull())
        {
            // 生产满了，就得等
            // 1. pthread_cond_wait调用是: a. 让调用线程等待 b. 自动释放曾经持有的_mutex锁以便于其他调用线程使用
            // c. 当条件满足，线程唤醒，pthread_cond_wait要求线程必须重新竞争_mutex锁，竞争成功，方可返回！！！
            // 因为如果可以直接不竞争锁向下执行，那么被唤醒的多个线程可能会同时访问临界区！！！
            // 之前：安全
            ++_product_wait_num;
            pthread_cond_wait(&_product_cond, &_mutex); //  只要等待，必定会有唤醒，唤醒的时候，就要继续从这个位置向下运行！！
            --_product_wait_num;
            // 之后：安全
        }
        _block_queue.push(in);
        // 这个时候最少有一个数据，叫消费者者来消费
        if (_consume_wait_num > 0) // 没有等待的消费者就不用通知
            pthread_cond_signal(&_consume_cond);
        // pthread_cond_broadcast(&_consume_cond);
        pthread_mutex_unlock(&_mutex);
        // pthread_cond_signal(&_consume_cond); // 也可以
    }

    void Pop(T *out)
    { // 消费者
        pthread_mutex_lock(&_mutex);

        // 不能用if，保证代码的健壮性
        // 考虑一种情况 ：只有1个生产者，有5个消费者

        // 此时没有数据，消费者先启动，那么5个消费者在条件变量下等待。
        // 然后生产者生产了1个数据，然后生产者broadcast唤醒了所有消费者
        // 此时有一个消费者竞争mutex锁成功，其他4个消费者在mutex锁下等待（所有消费者线程已唤醒，不再在条件变量下等待）
        // 那么当这个消费者消费完释放mutex锁后，这个等待的4个消费者中的一个消费者拿到锁，直接向下执行了！而此时队列已经没有数据了！那么就会出错。
        while (IsEmpty())
        {
            // 吃完了，就得等
            // 1. pthread_cond_wait调用是: a. 让调用线程等待 b. 自动释放曾经持有的_mutex锁以便于其他调用线程使用
            ++_consume_wait_num;
            pthread_cond_wait(&_consume_cond, &_mutex);
            --_consume_wait_num;
        }
        *out = _block_queue.front();
        _block_queue.pop();
        // 这个时候最少有一个空间，叫生产者来生产
        if(_product_wait_num > 0) // 没有生产者等待就不用通知
            pthread_cond_signal(&_product_cond);
        pthread_mutex_unlock(&_mutex);
    }

    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_product_cond);
        pthread_cond_destroy(&_consume_cond);
    }

private:
    queue<T> _block_queue;
    pthread_mutex_t _mutex;       // 互斥访问阻塞队列
    pthread_cond_t _product_cond; // 生产者条件变量
    pthread_cond_t _consume_cond; // 消费者条件变量
    int _cap;

    int _product_wait_num;
    int _consume_wait_num;
};

#endif
