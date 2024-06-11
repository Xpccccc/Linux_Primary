#include <iostream>
#include <memory>
#include "Task.hpp"
#include "Log.hpp"
#include "Threadpool.hpp"

// 单例模式
int main()
{
    EnableFile();
    LOG(DEBUG, "程序已经加载");
    sleep(3);
    Threadpool<Task> *tp = Threadpool<Task>::GetInstance(10);
    int cnt = 10;
    while (cnt--)
    {
        srand(time(nullptr) ^ cnt);
        int a = rand() % 10;
        int b = rand() % 20;
        Task t(a, b);
        LOG(DEBUG, "main thread : %s", t.stringDebug().c_str());
        // cout << "main thread - " << t.stringDebug() << endl;
        tp->Enqueue(t);
    }
    sleep(3);
    Threadpool<Task>::GetInstance();
    sleep(3);
    Threadpool<Task>::GetInstance();
    sleep(3);
    Threadpool<Task>::GetInstance();
    cnt = 5;
    while (cnt--)
    {
        srand(time(nullptr) ^ cnt);
        int a = rand() % 10;
        int b = rand() % 20;
        Task t(a, b);
        LOG(DEBUG, "main thread : %s", t.stringDebug().c_str());
        // cout << "main thread - " << t.stringDebug() << endl;
        tp->Enqueue(t);
    }
    tp->Stop();
    tp->Wait();
    sleep(3);
    return 0;
}

// int main()
// {
//     EnableFile();
//     LOG(DEBUG, "hello");
//     LOG(DEBUG, "hello %d", 1);
//     LOG(DEBUG, "hello hh %f", 2.1);
//     LOG(DEBUG, "hello hhhh %d %f", 1, 2.1);
//     LOG(DEBUG, "hello hhhhhh %d %d %c", 2, 31, 'c');
//     LOG(DEBUG, "hello hhhhhh %d %d %c %s", 2, 31, 'c', "oo");

//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello %d", 1);
//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello hh %f", 2.1);
//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello hhhh %d %f", 1, 2.1);
//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello hhhhhh %d %d %c", 2, 31, 'c');
//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello hhhhhh %d %d %c %s", 2, 31, 'c', "oo");

//     // Test(3,1,2,1);
//     // Test(7,1,2,1,23,4,5,8);

//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello");
//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello hh");
//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello hhhh");
//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello hhhhhh");
//     // LogMessage(__FILE__, __LINE__, DEBUG, "hello hhhhhhhhhh");

//     // unique_ptr<Threadpool<Task>> tp(new Threadpool<Task>(5));
//     unique_ptr<Threadpool<Task>> tp = make_unique<Threadpool<Task>>(5);
//     tp->InitThreadPool();
//     tp->Start();
//     int cnt = 10;
//     while (cnt--)
//     {
//         srand(time(nullptr) ^ cnt);
//         int a = rand() % 10;
//         int b = rand() % 20;
//         Task t(a, b);
//         LOG(DEBUG, "main thread : %s", t.stringDebug().c_str());
//         // cout << "main thread - " << t.stringDebug() << endl;
//         tp->Enqueue(t);
//     }

//     tp->Stop();
//     tp->Wait();
//     sleep(3);
//     return 0;
// }

// int main()
// {
//     // unique_ptr<Threadpool<Task>> tp(new Threadpool<Task>(5));
//     unique_ptr<Threadpool<Task>> tp = make_unique<Threadpool<Task>>(5);
//     tp->InitThreadPool();
//     tp->Start();
//     int cnt = 10;
//     while (cnt--)
//     {
//         srand(time(nullptr) ^ cnt);
//         int a = rand() % 10;
//         int b = rand() % 20;
//         Task t(a, b);
//         cout << "main thread - " << t.stringDebug() << endl;
//         tp->Enqueue(t);
//     }

//     tp->Stop();
//     tp->Wait();
//     sleep(3);
//     return 0;
// }