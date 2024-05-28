#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>
#include "Thread.hpp"
#include "Task.hpp"
#include "RingQueue.hpp"

using namespace ThreadModule;

using namespace std;

using Task_DIY = function<void(int)>;

using ringqueue = RingQueue<Task_DIY>;

void Print(int a)
{
    cout << " hh " << a << endl;
}

void Productor(ringqueue &rq, string &name)
{
    // sleep(5);
    int cnt = 1;
    while (true)
    {
        // Task_DIY t = Print;
        Task_DIY t = [](int cnt)
        { Print(cnt); }; // 使用传入的cnt参数
        rq.Enqueue(t);
        cout << name << " product : " << cnt++ << endl;
        sleep(1);
    }
}

void Consumer(ringqueue &rq, string &name)
{
    sleep(5);
    int cnt = 10;
    while (true)
    {
        Task_DIY t;
        rq.Pop(&t);
        cout << name << " : " << endl;
        t(cnt);
        ++cnt;
        sleep(1);
    }
}

void StartComm(vector<Thread<ringqueue>> &threads, int num, ringqueue &rq, func_t<ringqueue> func, const char *name)
{
    for (int i = 0; i < num; ++i)
    {
        string threadname = string(name) + to_string(i + 1);
        threads.emplace_back(func, rq, threadname);
    }
}

void StartProductor(vector<Thread<ringqueue>> &threads, int num, ringqueue &rq)
{
    StartComm(threads, num, rq, Productor, "Productor Thread - ");
}

void StartConsumer(vector<Thread<ringqueue>> &threads, int num, ringqueue &rq)
{
    StartComm(threads, num, rq, Consumer, "Consumer Thread - ");
}

void AllStart(vector<Thread<ringqueue>> &threads)
{
    for (auto &thread : threads)
    {
        // cout << "start : " << thread.name() << endl;
        thread.Start();
    }
}

void WaitAllThread(vector<Thread<ringqueue>> &threads)
{
    for (auto &thread : threads)
    {
        thread.Join();
    }
}

int main()
{
    ringqueue *rq = new ringqueue(5); // 阻塞队列，容量5，相当于超市
    vector<Thread<ringqueue>> threads;

    StartProductor(threads, 4, *rq);
    StartConsumer(threads, 3, *rq);
    AllStart(threads);
    WaitAllThread(threads);

    return 0;
}

// Thread传入自定义类型Task
// using ringqueue = RingQueue<Task>;

// void Productor(ringqueue &rq, string &name)
// {
//     // sleep(5);
//     int cnt = 10;
//     while (true)
//     {
//         srand(time(nullptr) ^ pthread_self());
//         int a = rand() % 10;
//         int b = rand() % 20;
//         Task t(a, b);
//         rq.Enqueue(t);
//         cout << name << " : " << t.stringDebug() << endl;
//         sleep(1);
//     }
// }

// void Consumer(ringqueue &rq, string &name)
// {
//     sleep(5);
//     while (true)
//     {
//         Task t;
//         rq.Pop(&t);
//         cout << name << " : " << t.stringResult() << endl;
//         sleep(1);
//     }
// }

// void StartComm(vector<Thread<ringqueue>> &threads, int num, ringqueue &rq, func_t<ringqueue> func, const char *name)
// {
//     for (int i = 0; i < num; ++i)
//     {
//         string threadname = string(name) + to_string(i + 1);
//         threads.emplace_back(func, rq, threadname);
//     }
// }

// void StartProductor(vector<Thread<ringqueue>> &threads, int num, ringqueue &rq)
// {
//     StartComm(threads, num, rq, Productor, "Productor Thread - ");
// }

// void StartConsumer(vector<Thread<ringqueue>> &threads, int num, ringqueue &rq)
// {
//     StartComm(threads, num, rq, Consumer, "Consumer Thread - ");
// }

// void AllStart(vector<Thread<ringqueue>> &threads)
// {
//     for (auto &thread : threads)
//     {
//         // cout << "start : " << thread.name() << endl;
//         thread.Start();
//     }
// }

// void WaitAllThread(vector<Thread<ringqueue>> &threads)
// {
//     for (auto &thread : threads)
//     {
//         thread.Join();
//     }
// }

// int main()
// {
//     ringqueue *rq = new ringqueue(5); // 阻塞队列，容量5，相当于超市
//     vector<Thread<ringqueue>> threads;

//     StartProductor(threads, 4, *rq);
//     StartConsumer(threads, 3, *rq);
//     AllStart(threads);
//     WaitAllThread(threads);

//     return 0;
// }
