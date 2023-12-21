#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
     int ret = fork();
     printf("hello proc : %d!, ret: %d\n", getpid(), ret);
     sleep(1);
     return 0;
}
