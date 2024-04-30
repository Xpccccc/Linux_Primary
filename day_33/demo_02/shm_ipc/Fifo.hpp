#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <assert.h>

using namespace std;

#define PATH "fifo"
#define MODE 0666

class Fifo
{
public:
    Fifo(const string &path) : _path(path)
    {
        //  创建管道文件
        umask(0);
        int n = mkfifo(path.c_str(), MODE);
        if (n == 0)
        {
            cout << "make fifo file:" << path << " sucess .." << endl;
        }
        else
        {
            //  创建失败
            cerr << "make fifo file "
                 << "errorno:" << errno << " error info:" << strerror(errno) << endl;
        }
    }
    ~Fifo()
    {
        int n = unlink(PATH);
        if (n < 0)
        {
            cerr << "remove fifo file "
                 << "errorno:" << errno << " error info:" << strerror(errno) << endl;
        }
        else
        {
            cout << "remove file:" << _path << " sucess ..." << endl;
        }
    }

private:
    string _path;
};

// 同步机制
class Sync
{
public:
    Sync() : rfd(-1), wfd(-1) {}

    void OpenReadOrDie()
    {
        rfd = open(PATH, O_RDONLY);
        if (rfd < 0)
            exit(1);
    }

    void OpenWriteOrDie()
    {
        wfd = open(PATH, O_WRONLY);
        if (wfd < 0)
            exit;
    }

    bool Wait()
    {
        bool ret = true;
        char c = 0; //  读一个字符
        ssize_t n = read(rfd, &c, sizeof(char));

        if (n == sizeof(char))
        {
            cout << "server wakeup, begin read shm..." << endl;
        }
        else
        {
            return false;
        }
        return ret;
    }

    void WakeUp()
    {
        char c = 0;
        ssize_t n = write(wfd, &c, sizeof(char));
        assert(n == sizeof(char));
        cout << "wakeup server...." << endl;
    }

    ~Sync() {}

private:
    int rfd;
    int wfd;
};