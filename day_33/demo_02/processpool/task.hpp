#pragma once

typedef void (*work_t)(int);
typedef void (*task_t)(int, pid_t);

void PrintLog(int fd, pid_t id)
{
    cout << "sub process:" << id << " fd : " << fd << " task is : "
         << "PrintLog task\n" << endl;
}

void ConnectMysql(int fd, pid_t id)
{
    cout << "sub process:" << id << " fd : " << fd << " task is : "
         << "ConnectMysql task\n" << endl;
}

void FlushPerson(int fd, pid_t id)
{
    cout << "sub process:" << id << " fd : " << fd << " task is : "
         << "FlushPerson task\n" << endl;
}

task_t task[3] = {PrintLog, ConnectMysql, ConnectMysql};

void worker(int fd)
{
    // 这里为什么fd总是3？ 因为每次父进程每创建一个子进程，关闭的读端都是3，那么下一次子进程的写端总是3
    // 从wfd = 0读取就行
    while (true)
    {
        uint32_t command_code = 0;
        ssize_t n = read(0, &command_code, sizeof(command_code)); // 从fd = 0读去放到command_code中
        if (n == sizeof(command_code))
        {
            if (command_code >= 3)
                continue;
            task[command_code](fd, getpid());
            sleep(1);
        }
        else if (n == 0)
        {
            // 父进程没有任务了，管道里面没有数据了就直接退出
            break;
        }
        // cout << "I am worker"<<endl;
        sleep(1);
    }
}