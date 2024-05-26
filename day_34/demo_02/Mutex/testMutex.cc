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
#include "LockGuard.hpp"

using namespace std;

using namespace ThreadModule;

// 抢票 
// 使用封装的Thread --  加锁 -- RAII
const int N = 4;
int tickets = 10000; // 共享资源，没有被保护

// // C++ mutex版本
// class ThreadData
// {
// public:
//     ThreadData(int &ticket, string &name, mutex &mutex) : _tickets(tickets), _name(name), _mutex(mutex), total(0) {}

// public:
//     int &_tickets;
//     string _name;
//     int total;
//     mutex &_mutex;
// };

// pthread_mutex_t 版本
class ThreadData
{
public:
    ThreadData(int &ticket, string &name, pthread_mutex_t& mutex) : _tickets(tickets), _name(name), _mutex(mutex), total(0) {}

public:
    int &_tickets;
    string _name;
    int total;
    pthread_mutex_t& _mutex;
};

void Route(ThreadData *td)
{
    while (td->_tickets)
    {
        // C++11
        // lock_guard<mutex> lock(td->_mutex);

        LockGuard guard(&td->_mutex); // RAII 思想，出了while作用域，自动解锁

        if (td->_tickets > 0)
        {
            usleep(1000); // 1毫秒
            printf("%s running , get tickets : %d \n", td->_name.c_str(),td->_tickets);

            ++td->total;
            --td->_tickets;
        }
        else
        {
            break;
        }
    }
}

int main()
{
    vector<Thread<ThreadData *>> threads;
    vector<ThreadData *> datas;

    // 初始化mutex
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, nullptr);

    // mutex mutex;

    // 创建一批线程
    for (int i = 0; i < N; ++i)
    {
        string name = "thread - " + to_string(i + 1);
        // ThreadData td;// 出了作用域就销毁
        ThreadData *td = new ThreadData(tickets, name, mutex);
        threads.emplace_back(Route, td, name);
        datas.emplace_back(td);
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
    }

    // 查看线程获得的票数
    for(auto& data : datas){
        cout << data->_name << " : tickets is : " << data->total << endl;
        delete data;
    }

    cout << "main thread quit ..." << endl;
    return 0;
}

// // 抢票
// // 使用封装的Thread --  加锁
// const int N = 4;
// int tickets = 10000; // 共享资源，没有被保护

// // // C++ mutex版本
// // class ThreadData
// // {
// // public:
// //     ThreadData(int &ticket, string &name, mutex &mutex) : _tickets(tickets), _name(name), _mutex(mutex), total(0) {}

// // public:
// //     int &_tickets;
// //     string _name;
// //     int total;
// //     mutex &_mutex;
// // };

// // pthread_mutex_t 版本
// class ThreadData
// {
// public:
//     ThreadData(int &ticket, string &name, pthread_mutex_t& mutex) : _tickets(tickets), _name(name), _mutex(mutex), total(0) {}

// public:
//     int &_tickets;
//     string _name;
//     int total;
//     pthread_mutex_t& _mutex;
// };

// void Route(ThreadData *td)
// {
//     while (td->_tickets)
//     {
      
//         // td->_mutex.lock(); // C++11
//         pthread_mutex_lock(&td->_mutex);
//         // pthread_mutex_lock(&g_mutex); // 加锁
//         if (td->_tickets > 0)
//         {
//             usleep(1000); // 1毫秒
//             printf("%s running , get tickets : %d \n", td->_name.c_str(),td->_tickets);

//             // td->_mutex.unlock(); // C++11
//             pthread_mutex_unlock(&td->_mutex);
//             // pthread_mutex_unlock(&g_mutex); // 解锁
//             ++td->total;
//             --td->_tickets;
//         }
//         else
//         {
//             // td->_mutex.unlock(); // C++11
//             pthread_mutex_unlock(&td->_mutex);
//             // pthread_mutex_unlock(&g_mutex); // 解锁
//             break;
//         }
//     }
// }

// int main()
// {
//     vector<Thread<ThreadData *>> threads;
//     vector<ThreadData *> datas;

//     // 初始化mutex
//     pthread_mutex_t mutex;
//     pthread_mutex_init(&mutex, nullptr);

//     // mutex mutex;

//     // 创建一批线程
//     for (int i = 0; i < N; ++i)
//     {
//         string name = "thread - " + to_string(i + 1);
//         // ThreadData td;// 出了作用域就销毁
//         ThreadData *td = new ThreadData(tickets, name, mutex);
//         threads.emplace_back(Route, td, name);
//         datas.emplace_back(td);
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
//     }

//     // 查看线程获得的票数
//     for(auto& data : datas){
//         cout << data->_name << " : tickets is : " << data->total << endl;
//         delete data;
//     }

//     cout << "main thread quit ..." << endl;
//     return 0;
// }

// // 抢票
// // 使用封装的Thread --  加锁 -- 自定义类传入
// const int N = 4;
// int tickets = 10000;                                 // 共享资源，没有被保护
// pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER; // 初始化

// class ThreadData
// {
// public:
//     ThreadData(int &ticket, string &name) : _tickets(tickets), _name(name), total(0) {}

// public:
//     int &_tickets;
//     string _name;
//     int total;
// };

// void Route(ThreadData *td)
// {
//     while (td->_tickets)
//     {
//         pthread_mutex_lock(&g_mutex); // 加锁
//         if (td->_tickets > 0)
//         {
//             usleep(1000); // 1毫秒
//             printf("%s running , get tickets : %d \n", td->_name.c_str(),td->_tickets);
//             pthread_mutex_unlock(&g_mutex); // 解锁
//             ++td->total;
//             --td->_tickets;
//         }
//         else
//         {
//             pthread_mutex_unlock(&g_mutex); // 解锁
//             break;
//         }
//     }
// }

// int main()
// {
//     vector<Thread<ThreadData *>> threads;
//     vector<ThreadData *> datas;

//     // 创建一批线程
//     for (int i = 0; i < N; ++i)
//     {
//         string name = "thread - " + to_string(i + 1);
//         // ThreadData td;// 出了作用域就销毁
//         ThreadData *td = new ThreadData(tickets, name);
//         threads.emplace_back(Route, td, name);
//         datas.emplace_back(td);
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
//     }

//     // 查看线程获得的票数
//     for (auto &data : datas)
//     {
//         cout << data->_name << " : tickets is : " << data->total << endl;
//         delete data;
//     }

//     cout << "main thread quit ..." << endl;
//     return 0;
// }

// // 抢票
// // 使用封装的Thread --  加锁
// const int N = 4;
// int tickets = 10000;                                 // 共享资源，没有被保护
// pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER; // 初始化

// void Route(int &rtickets)
// {
//     while (rtickets)
//     {
//         pthread_mutex_lock(&g_mutex); // 加锁
//         if (rtickets > 0)
//         {
//             usleep(1000); // 1毫秒
//             printf("get tickets : %d \n", rtickets);
//             pthread_mutex_unlock(&g_mutex); // 解锁
//             --rtickets;
//         }
//         else
//         {
//             pthread_mutex_unlock(&g_mutex); // 解锁
//             break;
//         }
//     }
// }

// int main()
// {
//     vector<Thread<int>> threads;

//     // 创建一批线程
//     for (int i = 0; i < N; ++i)
//     {
//         string name = "thread - " + to_string(i + 1);
//         threads.emplace_back(Route, tickets, name);
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