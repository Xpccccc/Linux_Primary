#include <iostream>
#include <vector>
#include <string>
#include "Thread.hpp"
#include "Task.hpp"
#include "BlockQueue.hpp"

using namespace ThreadModule;

using namespace std;

using Task_DIY = function<void()>;

using blockqueue_t = BlockQueue<Task_DIY>;

void Print()
{
    cout << "Print... " << endl;
}

void Productor(blockqueue_t &bq, string &name)
{
    // sleep(5);
    int cnt = 10;
    while (true)
    {
        Task_DIY t = Print;
        bq.Enqueue(t);
        cout << name << endl;
        sleep(1);
    }
}

void Consumer(blockqueue_t &bq, string &name)
{
    sleep(5);
    while (true)
    {
        Task_DIY t;
        bq.Pop(&t);
        cout << name << endl;
        t();
        sleep(1);
    }
}
void StartComm(vector<Thread<blockqueue_t>> &threads, int num, blockqueue_t &bq, func_t<blockqueue_t> func, const char *name)
{
    for (int i = 0; i < num; ++i)
    {
        string threadname = string(name) + to_string(i + 1);
        threads.emplace_back(func, bq, threadname);
        // threads.back().Start();
        // sleep(1);
    }
}

void StartProductor(vector<Thread<blockqueue_t>> &threads, int num, blockqueue_t &bq)
{
    StartComm(threads, num, bq, Productor, "Productor Thread - ");
}

void StartConsumer(vector<Thread<blockqueue_t>> &threads, int num, blockqueue_t &bq)
{
    StartComm(threads, num, bq, Consumer, "Consumer Thread - ");
}

void AllStart(vector<Thread<blockqueue_t>> &threads)
{
    for (auto &thread : threads)
    {
        cout << "start : " << thread.name() << endl;
        thread.Start();
    }
}

void WaitAllThread(vector<Thread<blockqueue_t>> &threads)
{
    for (auto &thread : threads)
    {
        thread.Join();
    }
}

int main()
{
    blockqueue_t *bq = new blockqueue_t(5); // 阻塞队列，容量5，相当于超市
    vector<Thread<blockqueue_t>> threads;

    StartProductor(threads, 3, *bq);
    StartConsumer(threads, 4, *bq);

    AllStart(threads);
    WaitAllThread(threads);

    return 0;
}

// // BlockQueue里面存Task
// using blockqueue_t = BlockQueue<Task>;

// void Productor(blockqueue_t &bq, string &name)
// {
//     // sleep(5);
//     while (true)
//     {
//         srand(time(nullptr));
//         int a = rand() % 10;
//         int b = rand() % 20;
//         Task t(a, b);
//         bq.Enqueue(t);
//         cout << name << " : " << t.stringDebug() << endl;
//         sleep(1);
//     }
// }

// void Consumer(blockqueue_t &bq, string &name)
// {
//     sleep(5);
//     while (true)
//     {
//         Task t;
//         bq.Pop(&t);
//         cout << name << " : " << t.stringResult() << endl;
//         sleep(1);
//     }
// }
// void StartComm(vector<Thread<blockqueue_t>> &threads, int num, blockqueue_t &bq, func_t<blockqueue_t> func, const char *name)
// {
//     for (int i = 0; i < num; ++i)
//     {
//         string threadname = string(name) + to_string(i + 1);
//         threads.emplace_back(func, bq, threadname);
//         // threads.back().Start();// 有问题，重入threads问题
//         // sleep(1);
//     }
// }

// void StartProductor(vector<Thread<blockqueue_t>> &threads, int num, blockqueue_t &bq)
// {
//     StartComm(threads, num, bq, Productor, "Productor Thread - ");
// }

// void StartConsumer(vector<Thread<blockqueue_t>> &threads, int num, blockqueue_t &bq)
// {
//     StartComm(threads, num, bq, Consumer, "Consumer Thread - ");
// }

// void AllStart(vector<Thread<blockqueue_t>> &threads)
// {
//     for (auto &thread : threads)
//     {
//         cout << "start : " << thread.name() << endl;
//         thread.Start();
//     }
// }

// void WaitAllThread(vector<Thread<blockqueue_t>> &threads)
// {
//     for (auto &thread : threads)
//     {
//         thread.Join();
//     }
// }

// int main()
// {
//     blockqueue_t *bq = new blockqueue_t(5); // 阻塞队列，容量5，相当于超市
//     vector<Thread<blockqueue_t>> threads;

//     StartProductor(threads, 4, *bq);
//     StartConsumer(threads, 3, *bq);

//     AllStart(threads);
//     WaitAllThread(threads);

//     return 0;
// }

// // BlockQueue里面存int
// void Productor(BlockQueue<int> &bq, string &name)
// {
//     // sleep(2);
//     int cnt = 10;
//     while (true)
//     {
//         bq.Enqueue(cnt);
//         // cout << "Productor... "t  << cnt << endl;
//         cout << name << " : " << cnt-- << endl;
//         sleep(1);
//     }
// }

// void Consumer(BlockQueue<int> &bq, string &name)
// {
//     sleep(2);
//     while (true)
//     {
//         int cnt = 0;
//         bq.Pop(&cnt);
//         // cout << "Consumer... " << cnt << endl;
//         cout << name << " : " << cnt << endl;
//         sleep(1);
//     }
// }
// void StartComm(vector<Thread<BlockQueue<int>>> &threads, int num, BlockQueue<int> &bq, func_t<BlockQueue<int>> func, const char *name)
// {
//     for (int i = 0; i < num; ++i)
//     {
//         string threadname = string(name) + to_string(i + 1);
//         threads.emplace_back(func, bq, threadname);
//         // threads.back().Start(); // 有问题，重入threads问题
//         // sleep(1);
//     }
// }

// void StartProductor(vector<Thread<BlockQueue<int>>> &threads, int num, BlockQueue<int> &bq)
// {
//     StartComm(threads, num, bq, Productor, "Productor Thread - ");
// }

// void StartConsumer(vector<Thread<BlockQueue<int>>> &threads, int num, BlockQueue<int> &bq)
// {
//     StartComm(threads, num, bq, Consumer, "Consumer Thread - ");
// }

// void AllStart(vector<Thread<BlockQueue<int>>> &threads)
// {
//     for (auto &thread : threads)
//     {
//         cout << "start : " << thread.name() << endl;
//         thread.Start();
//     }
// }

// void WaitAllThread(vector<Thread<BlockQueue<int>>> &threads)
// {
//     for (auto &thread : threads)
//     {
//         thread.Join();
//     }
// }

// int main()
// {
//     BlockQueue<int> *bq = new BlockQueue<int>(5); // 阻塞队列，容量5，相当于超市
//     vector<Thread<BlockQueue<int>>> threads;

//     StartProductor(threads, 1, *bq);
//     StartConsumer(threads, 1, *bq);

//     AllStart(threads);
//     WaitAllThread(threads);

//     return 0;
// }
