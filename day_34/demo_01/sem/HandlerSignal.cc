#include <iostream>
#include <csignal>
#include <assert.h>
#include <string.h>
#include <unistd.h>

using namespace std;

// 异常  --  异常没有终止，操作系统还有正常执行进程调度，那么上下文会进行保护，下一次调度到该进程的时候又会恢复，进程在运行的时候就会一直异常
void handler(int sig)
{
    cout << "get a sig, signo: " << sig << endl;
    sleep(1);
}

int main()
{
    signal(SIGFPE, handler);
    signal(SIGSEGV, handler);
    signal(SIGQUIT, handler);

    //除0
    int a = 10;
    a /= 0;

    // 空指针
    // int *p = nullptr;
    // *p = 1;

    while (true)
    {
        cout << "pid :" << getpid() << endl;
        sleep(1);
    }

    return 0;
}

// // alarm闹钟
// int g_val = 0;

// void handler(int sig)
// {
//     // cout << "get a sig, signo:" << sig << ", g_val:" << g_val << endl;

//     // alarm(2);
//     // cout << "闹钟到啦！" << endl;

//     int n = alarm(2); // 每隔2秒响一次 , alarm的返回值是：如果之前有闹钟还没到时间，这个返回值是最近的闹钟还剩余的时间，如果之前没有闹钟，那么返回0Í

//     cout << "还剩：" << n << " 秒" << endl;
//     // exit(0);
// }

// int main()
// {

//     signal(SIGALRM, handler);

//     alarm(50); // 响一次

//     int cnt = 0;

//     // while (true)
//     // {
//     //     ++g_val;
//     // }

//     while (true)
//     {
//         sleep(1);
//         cout << "cnt :" << cnt++ << ", pid: " << getpid() << endl; // IO很慢
//         if (cnt == 20)
//         {
//             // 取消所有闹钟
//             int ret = alarm(0);
//             cout << "ret: " << ret << endl;

//         }
//     }
//     return 0;
// }

// void handler(int signo)
// {
//     cout << "get a signal,no: " << signo << endl;
// }

// int main()
// {
//     // signal(2, handler);
//     int cnt = 0;
//     while (true)
//     {
//         cout << "cnt: " << cnt++ << endl;
//         sleep(1);
//         if (cnt == 5)
//         {
//             cout << "send 2 to caller" << endl;
//             // raise(2);
//             abort();
//         }
//     }
//     return 0;
// }

// // mykill -9 pid
// int main(int argc, char *argv[])
// {
//     if (argc != 3)
//     {
//         cout << "Usage:" << argv[0] << " -signo pid" << endl;
//         exit(1);
//     }

//     int signo = stoi(argv[1] + 1);

//     int pid = stoi(argv[2]);

//     int n = kill(pid, signo);
//     if (n < 0)
//     {
//         cerr << "kill error ,errno:" << errno << ", error string: " << strerror(errno) << endl;
//     }
//     return 0;
// }

// void handler(int signo)
// {
//     cout << "get a signal,no: " << signo << endl;
// }

// int main()
// {

//     // handler调用完了，handler方法会被立即执行吗？不是，只是设置对应信号的处理方法
//     // 为未来我们收到对应的信号才执行handler方法
//     // ctrl + c 退出进程其实也是用的SIGINT信号 可以使用signal(SIGINT, handler);来测试，也就是运行时候ctrl + c看会不会退出
//     signal(SIGINT, handler); // ctrl + c 是SIGINT信号，编号2
//     signal(SIGQUIT, handler); // ctrt + \ 是SIGQUIT信号，编号3

//     while (true)
//     {
//         cout << "I am process,pid :" << getpid() << endl;
//         sleep(1);
//     }

//     return 0;
// }
