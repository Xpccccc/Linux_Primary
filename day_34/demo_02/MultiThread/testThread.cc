#include <iostream>
#include <unistd.h>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <thread>
#include <string>
#include <mutex>
#include <pthread.h>
#include "Thread.hpp"

using namespace std;

using namespace ThreadModule;


// 抢票  -- 没有对临界资源上锁，存在问题
// 使用封装的Thread
const int N = 4;
int tickets = 10000; // 共享资源，没有被保护

void Route(int &rtickets)
{
    while (rtickets)
    {
        // cout << "rtickets : " << rtickets << ", &rtickets : " << &rtickets << endl;
        if(rtickets > 0){
            usleep(1000); // 1毫秒
            printf("get tickets : %d \n",rtickets);
            --rtickets;
        }else{
            break;
        }
    }
}

int main()
{
    vector<Thread<int>> threads;
    // cout << "tickets : " << tickets << ", &tickes : " << &tickets << endl;

    // 创建一批线程
    for (int i = 0; i < N; ++i)
    {
        string name = "thread - " + to_string(i + 1);
        threads.emplace_back(Route, tickets, name);
    }

    // 启动一批线程
    for (auto &thread : threads)
    {
        thread.Start();
    }

    // 等待一批线程
    for (auto &thread : threads)
    {
        thread.Join();
        cout << "wait thread done , name :  " << thread.name() << endl;
    }

    cout << "main thread quit ..." << endl;
    return 0;
}

// // 使用封装的Thread
// const int N = 10;
// int g_val = 100;

// void Print(int &num)
// {
//     while (num)
//     {
//         cout << "I am new thread  , num : " << num-- << endl;
//         sleep(1);
//     }
// }

// int main()
// {
//     vector<Thread<int>> threads;
//     // 创建一批线程
//     for (int i = 0; i < N; ++i)
//     {
//         string name = "thread - " + to_string(i + 1);

//         // 错误写法
//         // int val = 100;// 局部变量，出了for（下一次进for）就销毁
//         // threads.emplace_back(Print, val, name);

//         threads.emplace_back(Print, g_val, name);
//     }

//     // 启动一批线程
//     for (auto &thread : threads)
//     {
//         thread.Start();
//     }

//     // 等待一批线程
//     for (auto &thread : threads)
//     {
//         thread.Join();
//         cout << "wait thread done , name :  " << thread.name() << endl;
//     }

//     cout << "main thread quit ..." << endl;
//     return 0;
// }

// void Print(int x)
// {
//     cout << "hh" << endl;
// }

// int main()
// {
//     Thread<int> t(Print, 10);
//     t.Start();
//     t.Join();
//     return 0;
// }

// // __thread可以给不同线程分配不同的局部变量 -- 其实也就是在各线程入口函数中省得再手动创建一个变量 -- 线程局部存储
// __thread int g_val = 10;
// __thread uint64_t starttime = 0;

// void *newThread1(void *arg)
// {
//     starttime = time(nullptr);
//     string threadname = static_cast<char *>(arg);
//     while (g_val)
//     {
//         sleep(1);
//         cout << "I am new thread, name : " << threadname << " , startime : " << starttime << " , g_val : " << g_val << " , &g_val : " << &g_val << endl;
//     }

//     return (void *)123;
// }

// void *newThread2(void *arg)
// {
//     sleep(3);
//     starttime = time(nullptr);
//     string threadname = static_cast<char *>(arg);
//     while (g_val)
//     {
//         sleep(1);
//         cout << "I am new thread, name : " << threadname << " , startime : " << starttime << " , g_val : " << g_val << " , &g_val : " << &g_val << endl;
//         --g_val;
//     }

//     return (void *)123;
// }

// int main()
// {
//     pthread_t tid1;
//     pthread_t tid2;
//     pthread_create(&tid1, nullptr, newThread1, (void *)"thread 1");
//     pthread_create(&tid2, nullptr, newThread2, (void *)"thread 2");

//     pthread_join(tid1, nullptr);
//     pthread_join(tid2, nullptr);

//     cout << "main thread quit ..." << endl;
//     return 0;
// }

// // 线程独立栈结构
// void *newThread(void *arg)
// {
//     string threadname = static_cast<char *>(arg);
//     int cnt =5;
//     while (true)
//     {
//         sleep(1);
//         cout << "I am new thread, name : " << threadname << ", cnt : " << cnt << " , &cnt : " << &cnt << endl;
//     }

//     return (void *)123;
// }

// int main()
// {
//     pthread_t tid1;
//     pthread_t tid2;
//     pthread_create(&tid1, nullptr, newThread, (void *)"thread 1");
//     pthread_create(&tid2, nullptr, newThread, (void *)"thread 2");

//     pthread_join(tid1,nullptr);
//     pthread_join(tid2,nullptr);

//     cout << "main thread quit ..." << endl;
//     return 0;
// }

// // 线程是可以分离的
// string ToHex(pthread_t tid)
// {
//     char id[64];
//     snprintf(id, sizeof(id), "0x%lx", tid);
//     return id;
// }

// void *newThread(void *arg)
// {
//     //  线程是可以分离的，默认线程是joinable的
//     // 分离线程 1 分离线程并不是该线程和主线程一点关系没有了，还是属于同一个进程，还是共享地址空间，并且主线程退出，新线程也会退出，
//     // 只是主线程不必等待新线程，新线程自己执行完会主动释放资源
//     pthread_detach(pthread_self());
//     string threadname = static_cast<char *>(arg);
//     int cnt = 5;
//     while (cnt)
//     {
//         sleep(1);
//         cout << "I am new thread, name : " << threadname << " , pid : " << getpid() << " , id : " << ToHex(pthread_self()) << endl;
//         --cnt;
//     }

//     return (void *)123;
// }

// int main()
// {
//     pthread_t tid;
//     pthread_create(&tid, nullptr, newThread, (void *)"thread 1");
//     // 分离线程 2
//     // pthread_detach(tid);
//     int cnt = 10;
//     while (cnt)
//     {
//         cout << "I am main thread , pid : " << getpid() << " , tid : " << ToHex(tid) << " , id : " << ToHex(pthread_self()) << endl;
//         sleep(1);
//         --cnt;
//     }

//     // 分离线程后不用等待新线程的死活
//     // 一般都是主线程永远最后退出或者死循环不退出！ 无论线程数join还是detach
//     cout << "main thread quit ..." << endl;
//     return 0;
// }

// // C++11 多线程
// void newThread(int num)
// {
//     while (num)
//     {
//         cout << "I am new thread , num : " << num << endl;
//         sleep(1);
//         num--;
//     }
// }

// int main()
// {
//     thread t1(newThread, 4);
//     thread t2(newThread, 5);
//     thread t3(newThread, 6);
//     // while (true)
//     // {
//     //     cout << "I am main thread" << endl;
//     //     sleep(1);
//     // }

//     t1.join();
//     t2.join();
//     t3.join();
//     cout << "main thread quit ..." << endl;

//     return 0;
// }

// // 创建多线程
// const int N = 5;

// class Task
// {
// public:
//     Task(int x = 1, int y = 1) : _x(x), _y(y) {}

//     int Execute()
//     {
//         return _x + _y;
//     }

// private:
//     int _x;
//     int _y;
// };

// class ThreadData
// {
// public:
//     ThreadData(int x, int y, string threadname) : _t(x, y), _threadname(threadname) {}

//     string threadName()
//     {
//         return _threadname;
//     }

//     int run()
//     {
//         return _t.Execute();
//     }

// private:
//     string _threadname;
//     Task _t;
// };

// class Result
// {
// public:
//     void setResult(int result, string threadname)
//     {
//         _result = result;
//         _threadname = threadname;
//     }

//     void Print()
//     {
//         cout << " result : " << _result << " , threadname : " << _threadname << endl;
//     }

// private:
//     int _result;
//     string _threadname;
// };

// void *newThread(void *arg)
// {

//     ThreadData *td = static_cast<ThreadData *>(arg);

//     string name = td->threadName();
//     Result *res = new Result(); // 这里得new  ！

//     int ret = td->run();
//     res->setResult(ret, name);

//     sleep(1);
//     delete td;
//     return res;

//     // // string threadname = static_cast<char *>(arg);
//     // const char *threadname = (char *)arg;
//     // int cnt = 5;
//     // while (cnt--)
//     // {
//     //     cout << "I am new thread , name : " << threadname << endl;
//     //     sleep(1);
//     // }

//     // delete[] threadname;
//     // return nullptr;
// }

// int main()
// {
//     vector<pthread_t> threads;

//     for (int i = 0; i < N; ++i)
//     {
//         // char *threadname = new char[64];
//         // snprintf(threadname, 64, "Thread - %d", i);

//         char threadname[64];
//         snprintf(threadname, sizeof(threadname), "Thread - %d", i);
//         ThreadData *td = new ThreadData(10, i, threadname);

//         pthread_t tid;
//         pthread_create(&tid, nullptr, newThread, td);
//         // pthread_create(&tid, nullptr, newThread, (void *)threadname);
//         threads.push_back(tid);
//     }

//     vector<Result *> result_set;

//     void *ret = nullptr;

//     // 等待线程及获取返回值
//     for (auto &tid : threads)
//     {
//         pthread_join(tid, &ret);
//         result_set.push_back((Result *)ret);
//     }

//     // 打印查看
//     for (auto &res : result_set)
//     {
//         res->Print();
//         delete res;
//     }

//     sleep(3);
//     return 0;
// }

// // 同一个进程下的线程。大部分资源是共享的，地址空间也是共享的
// int g_val = 100;

// string ToHex(pthread_t tid)
// {
//     char id[64];
//     snprintf(id, sizeof(id), "0x%lx", tid);
//     return id;
// }

// void *newThread(void *arg)
// {
//     string threadname = static_cast<char *>(arg);
//     int cnt = 5;
//     while (cnt)
//     {
//         printf("new thread , g_val : %d , &g_val : %p \n", g_val, &g_val);
//         // cout << " I am " << threadname << " thread , pid : " << getpid() << " , id :" << ToHex(pthread_self()) << endl;
//         cout << "----------------------------------" << endl;
//         ++g_val;
//         sleep(1);
//         --cnt;
//     }

//     return (void *)222;
// }

// int main()
// {

//     pthread_t tid;

//     int n = pthread_create(&tid, nullptr, newThread, (void *)"Thread-1");
//     int cnt = 10;
//     while (cnt)
//     {
//         printf("main thread , g_val : %d , &g_val : %p \n", g_val, &g_val);

//         // cout << " I am main thread , pid : " << getpid() << " , id :" << ToHex(pthread_self()) << " ,tid : " << ToHex(tid) << endl;
//         cout << "----------------------------------" << endl;

//         sleep(1);
//         --cnt;
//     }

//     sleep(3);

//     void *ret = nullptr;
//     n = pthread_join(tid, &ret); // 返回值

//     cout << " main thread quit , ret : " << (long long)ret << " , n = " << n << endl;

//     return 0;
// }

// //  线程异常
// string ToHex(pthread_t tid)
// {
//     char id[64];
//     snprintf(id, sizeof(id), "0x%lx", tid);
//     return id;
// }

// void *newThread(void *arg)
// {
//     string threadname = static_cast<char *>(arg);
//     cout << "I am new thread, name : " << threadname << " , pid : " << getpid() << " , id : " << ToHex(pthread_self()) << endl;

//     // 异常
//     int *p = nullptr;
//     *p = 1;

//     return (void *)123;
// }

// int main()
// {

//     pthread_t tid;

//     int n = pthread_create(&tid, nullptr, newThread, (void *)"Thread-1");
//     sleep(1);
//     pthread_cancel(tid);
//     void *ret = nullptr;
//     n = pthread_join(tid, &ret); // 返回值
//     cout << " main thread quit , ret : " << (long long)ret << " , n = " << n << endl;
//     sleep(1);
//     return 0;
// }

// // pthread_cancel 线程终止
// string ToHex(pthread_t tid)
// {
//     char id[64];
//     snprintf(id, sizeof(id), "0x%lx", tid);
//     return id;
// }

// void *newThread(void *arg)
// {
//     string threadname = static_cast<char *>(arg);
//     cout << "I am new thread, name : " << threadname << " , pid : " << getpid() << " , id : " << ToHex(pthread_self()) << endl;
//     sleep(100);
//     return (void *)123;
// }

// int main()
// {

//     pthread_t tid;

//     int n = pthread_create(&tid, nullptr, newThread, (void *)"Thread-1");
//     sleep(1);
//     pthread_cancel(tid);
//     void *ret = nullptr;
//     n = pthread_join(tid, &ret); // 返回值
//     cout << " main thread quit , ret : " << (long long)ret << " , n = " << n << endl;
//     sleep(1);
//     return 0;
// }

// // pthread_exit 线程终止
// string ToHex(pthread_t tid)
// {
//     char id[64];
//     snprintf(id, sizeof(id), "0x%lx", tid);
//     return id;
// }

// void *newThread(void *arg)
// {
//     string threadname = static_cast<char *>(arg);
//     cout << "I am new thread, name : " << threadname  << " , pid : "<< getpid() << " , id : " << ToHex(pthread_self()) << endl;

//     pthread_exit((void *)12); // 这里不正常退出，返回的就是(void*)12

// }

// int main()
// {

//     pthread_t tid;

//     int n = pthread_create(&tid, nullptr, newThread, (void *)"Thread-1");

//     void *ret = nullptr;
//     n = pthread_join(tid, &ret); // 返回值

//     cout << " main thread quit , ret : " << (long long)ret << " , n = " << n << endl;

//     return 0;
// }

// // 线程等待
// string ToHex(pthread_t tid)
// {
//     char id[64];
//     snprintf(id, sizeof(id), "0x%lx", tid);
//     return id;
// }

// void *newThread(void *arg)
// {
//     string threadname = static_cast<char *>(arg);
//     int cnt = 5;
//     while (cnt)
//     {
//         cout << "I am new thread, pid : " << getpid() << " , id : " << ToHex(pthread_self()) << endl;
//         sleep(1);
//         --cnt;
//     }

//     return nullptr;
// }

// int main()
// {

//     pthread_t tid;

//     int n = pthread_create(&tid, nullptr, newThread, (void *)"Thread-1");

//     sleep(1);
//     cout << "I am main thread, pid : " << getpid() << " , tid : " << ToHex(tid) << " , id : " << ToHex(pthread_self()) << endl;

//     // 线程等待
//     pthread_join(tid, nullptr);
//     sleep(5);

//     cout << " main thread quit " << endl;

//     return 0;
// }

// // 线程函数使用
// void *newThread(void *arg)
// {
//     while (1)
//     {
//         cout << "I am new thread ... ,pid : " << getpid() << endl;
//         sleep(1);
//     }
// }

// int main()
// {
//     pthread_t tid;
//     int n = pthread_create(&tid, nullptr, newThread, nullptr);

//     assert(n == 0);
//     while (1)
//     {
//         cout << "I am main thread ... ,pid : " << getpid() << endl;
//         sleep(1);
//     }

//     return 0;
// }
