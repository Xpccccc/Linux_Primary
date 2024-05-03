#include <iostream>
#include <string.h>

#include "Comm.hpp"

using namespace std;

int main()
{

    int fd = open(PATH, O_WRONLY);

    const char* msg = "i am process A";
    ssize_t n1 = write(fd, msg, strlen(msg));

    return 0;
}