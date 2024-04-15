#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>
#include <ctime>

using namespace std;

#include "task.hpp"

enum
{
    UsageErr = 1,
    Sub_processNumErr,
    PipeErr
};

class Channel
{
public:
    Channel(int wfd, int sub_id, string name) : _wfd(wfd), _sub_process_id(sub_id), _name(name) {}
    ~Channel() {}

    void Debug()
    {
        cout << "_wfd :" << _wfd;
        cout << ",_sub_process_id :" << _sub_process_id;
        cout << ",_name :" << _name << endl;
    }

    int wfd() { return _wfd; }
    string name() { return _name; }
    pid_t pid() { return _sub_process_id; }
    void Close() { close(_wfd); }

private:
    int _wfd;
    int _sub_process_id;
    string _name;
};

class ProcessPool
{
public:
    ProcessPool(int sub_porcessNum) : _sub_processNum(sub_porcessNum) {}
    ~ProcessPool() {}
    int CreateProcess(work_t work)
    {
        vector<int> fds; // 创建一个空的文件描述符数组，用来记录每个进程需要关闭的描述符
        // 因为子进程会继承父进程的文件描述符表，那么当父进程创建的越多，就越多子进程进程指向文件的写端，如果不一一关闭个子进程不属于自己的写文件描述符
        // 会导致如果按顺序关闭文件描述符的时候，子进程会阻塞，因为有写文件描述符没关完全。
        for (int i = 0; i < _sub_processNum; ++i)
        {
            int pipefd[2]{0};
            int n = pipe(pipefd);
            if (n < 0)
                return PipeErr;

            pid_t id = fork();
            if (id == 0)
            {
                if (!fds.empty())
                {   
                    cout << "close fd: ";
                    
                    for (auto e : fds)
                    {
                        close(e);
                        cout << e << " ";
                    }
                    cout << endl;
                }
                close(pipefd[1]);
                // child -- r
                dup2(pipefd[0], 0);
                work(pipefd[0]);
                // sleep(100);
                exit(0); // 正常退出
            }
            sleep(2);

            string cname = "Channel - " + to_string(i);

            close(pipefd[0]);
            // father -- w

            _channels.push_back(Channel(pipefd[1], id, cname));
            fds.push_back(pipefd[1]); // 记录文件描述符，给下一个子进程用来关闭该文件描述符
        }
        return 0;
    }

    void Debug()
    {

        for (auto &e : _channels)
        {
            e.Debug();
        }
    }

    int NextChannel()
    {
        static int next = 0;
        int c = next++;
        next %= _channels.size();
        return c;
    }

    int NextTask()
    {
        return rand() % 3;
    }

    void SendTaskCode(int channel, int code)
    {
        cout << "send code :" << code << " to " << _channels[channel].name() << "  sub process id: " << _channels[channel].pid() << endl;
        write(_channels[channel].wfd(), &code, sizeof(code)); // 把code写到_channels[channel].wfd()中，去给worker中的read读去code的值
    }

    // 先关闭子进程
    void KillAll()
    {
        for (auto &e : _channels)
        {
            e.Close();
            cout << e.name() << " close done "
                 << " sub process quit now:" << e.pid() << endl;
        }
    }

    // 再等待子进程，回收资源
    void Wait()
    {

        for (auto &e : _channels)
        {
            pid_t id = e.pid();
            pid_t rid = waitpid(id, nullptr, 0);
            if (id == rid)
                cout << "wait sub process:" << id << " sucess..." << endl;
        }
    }

    //  直接关闭加等待一步到位
    void KillAndWait()
    {
        for (auto &e : _channels)
        {
            e.Close();
            cout << e.name() << " close done "
                 << " sub process quit now:" << e.pid() << endl;
            pid_t id = e.pid();
            pid_t rid = waitpid(id, nullptr, 0);
            if (id == rid)
                cout << "wait sub process:" << id << " sucess..." << endl;
        }
    }

private:
    vector<Channel> _channels;
    int _sub_processNum;
};

void CtrlProcessPool(ProcessPool *processpool_ptr, int cnt)
{

    while (cnt)
    {
        // a.选择一个进程和通道
        int channel = processpool_ptr->NextChannel();

        // b.选择一个任务
        int code = processpool_ptr->NextTask();

        // c.发送任务
        processpool_ptr->SendTaskCode(channel, code);

        cnt--;
        sleep(1);
    }
}

void Usage_Command()
{
    cout << "Usage: ./processpool number" << endl;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        Usage_Command();
        return UsageErr;
    }

    srand((uint32_t)time(nullptr));
    int sub_processNum = stoi(argv[1]);
    if (sub_processNum <= 0)
        return Sub_processNumErr;

    // 1.创建通信信道和子进程
    ProcessPool *processpool_ptr = new ProcessPool(sub_processNum);
    processpool_ptr->CreateProcess(worker);
    // processpool_ptr->Debug();

    // 2.控制子进程
    CtrlProcessPool(processpool_ptr, 10);
    cout << "task done ..." << endl;

    // sleep(100);

    // 3.回收子进程
    // processpool_ptr->KillAll();
    // processpool_ptr->Wait();
    processpool_ptr->KillAndWait();
    // sleep(100);
    cout << "wait sub process done ..." << endl;
    return 0;
}