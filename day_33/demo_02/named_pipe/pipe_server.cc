#include "Comm.hpp"

int main()
{
    // 创建管道文件
    Fifo fifo(PATH);

    int rfd = open(PATH, O_RDONLY);
    if (rfd < 0)
    {
        cerr << "open error,  "
             << "errorno:" << errno << " error info:" << strerror(errno) << endl;
    }
    char buff[1024];
    while (true)
    {
        ssize_t n = read(rfd, buff, sizeof(buff) - 1);
        if (n > 0)
        {
            buff[n] = 0;
            cout << "get message :" << buff <<endl;
        }
        else if (n == 0)
        {
            cout << "read done .." << endl;
            break;
        }
        else
        {
            cerr << "read error,  "
                 << "errorno:" << errno << " error info:" << strerror(errno) << endl;
            break;
        }
    }
    close(rfd);
    return 0;
}