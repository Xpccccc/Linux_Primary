#include <iostream>

#include "Comm.hpp"

using namespace std;

int main()
{
    // 创建命名管道
    int n = mkfifo(PATH, 0666);

    int fd = open(PATH, O_RDONLY);

    char buff[1024];

    ssize_t n1 = read(fd, buff, sizeof(buff));
    buff[n1] = '\0';

    printf("%s\n",buff);
    return 0;
}