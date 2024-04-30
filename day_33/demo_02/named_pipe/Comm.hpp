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