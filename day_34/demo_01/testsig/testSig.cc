#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>

using namespace std;

void CleanupChild(int signo)
{

    if (signo == SIGCHLD)
    {
        while (true)
        {
            // 50个退出，50个没有 的情况 --  非阻塞等待
            pid_t rid = waitpid(-1, nullptr, WNOHANG); // -1 : 回收任意一个子进程
            if (rid > 0)
            {
                cout << "wait child success: " << rid << endl;
            }
            else if (rid <= 0)
                break;
        }
    }
    cout << "wait sub process done" << endl;
}

int main()
{
    // signal(SIGCHLD, CleanupChild);
    signal(SIGCHLD, SIG_IGN);

    for (int i = 0; i < 100; i++)
    {
        pid_t id = fork();
        if (id == 0)
        {
            // child
            int cnt = 5;
            while (cnt--)
            {
                cout << "I am child process: " << getpid() << endl;
                sleep(1);
            }
            cout << "child process died" << endl;
            exit(0);
        }
    }

    // father
    while (true)
        sleep(1);

    return 0;
}

// // sigaction
// void PrintSigset(const sigset_t &block)
// {
//     cout << "pending bitmap : ";
//     for (int signo = 31; signo >= 1; --signo)
//     {
//         if (sigismember(&block, signo))
//             cout << "1";
//         else
//             cout << "0";
//     }
// }

// void handler(int sig)
// {
//     sigset_t pending;
//     sigemptyset(&pending);
//     while (true)
//     {
//         int n = sigpending(&pending);
//         assert(n == 0);

//         PrintSigset(pending);
//         cout << endl;
//         sleep(1);
//     }
// }

// int main()
// {
//     cout << "pid : " << getpid() << endl;
//     struct sigaction act, oact;
//     act.sa_handler = handler;
//     act.sa_flags = 0;
//     sigemptyset(&act.sa_mask);

//     sigaddset(&act.sa_mask, 2);
//     sigaddset(&act.sa_mask, 3);
//     sigaction(2, &act, &oact);

//     while (true)
//         sleep(1);
//     return 0;
// }

// void PrintSigset(const sigset_t &block)
// {
//     cout << "pending bitmap : ";
//     for (int signo = 31; signo >= 1; --signo)
//     {
//         if (sigismember(&block, signo))
//             cout << "1";
//         else
//             cout << "0";
//     }
// }

// void handler(int sig)
// {
//     sigset_t pending;
//     sigemptyset(&pending);
//     int n = sigpending(&pending);
//     assert(n == 0);

//     cout << "递达中..." << endl;
//     PrintSigset(pending); // 0 ，递达之前pending位图2号信号已经清零
//     cout << endl;
//     cout << sig << " 号信号已递达..." << endl;
// }

// int main()
// {

//     // 捕捉2号信号
//     signal(2, handler);

//     // 1. 屏蔽2号信号
//     sigset_t block; // 用户在栈上开辟了空间
//     sigemptyset(&block);
//     sigaddset(&block, 2);

//     // // test：屏蔽所有信号？ 9,19号信号不能被屏蔽，18号特殊信号这里也不能屏蔽（看编译器）
//     // for(int i = 1; i <= 31; ++i)
//     //     sigaddset(&block, i);

//     sigset_t oblock;
//     // 1.1 开始屏蔽2号信号，其实就是设置进入内核中
//     int n = sigprocmask(SIG_SETMASK, &block, &oblock);
//     assert(n == 0);

//     cout << "block 2 sig success ..." << endl;
//     cout << "pid : " << getpid() << endl;

//     int cnt = 1;
//     while (true)
//     {
//         // 2. 获取进程的pending位图
//         sigset_t pending;
//         sigemptyset(&pending);
//         n = sigpending(&pending);
//         assert(n == 0);

//         // 3. 打印pending位图中的收到的信号
//         PrintSigset(pending);
//         cout << "  cnt : " << cnt;
//         cout << endl;

//         // 4. 解除对2号信号的屏蔽
//         if (cnt == 20)
//         {
//             cout << "解除对2号信号的屏蔽...." << endl;
//             n = sigprocmask(SIG_UNBLOCK, &block, &oblock);
//             assert(n == 0);
//         }
//         cnt++;
//         sleep(1);
//     }

//     // // core dump
//     // pid_t id = fork();
//     // if (id == 0)
//     // {
//     //     int a = 10;
//     //     a /= 0;
//     //     exit(100);
//     // }

//     // int status = 0;
//     // pid_t rid = waitpid(id, &status, 0);
//     // if (rid > 0)
//     // {
//     //     cout << "exit code : " << ((status >> 8) & 0xFF) << endl; // 没有意义，因为是异常退出，那么exit(100)不会执行
//     //     cout << "exit core dump : " << ((status >> 7) & 0x1) << endl;
//     //     cout << "exit sig : " << (status & 0x7f) << endl;
//     // }

//     // // 除0
//     // // int a = 10;
//     // // a /= 0;

//     // // 空指针
//     // int *p = nullptr;
//     // *p = 1;

//     // // while (true)
//     // // {
//     // //     cout << "pid :" << getpid() << endl;
//     // //     sleep(1);
//     // // }

//     return 0;
// }