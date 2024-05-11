#include <stdio.h>
#include <signal.h>

volatile int flag = 0;
void handler(int sig)
{
    printf("chage flag 0 to 1\n");
    flag = 1;
}
int main()
{
    signal(2, handler);
    while (!flag)
        ;

    printf("process quit normal\n");
    return 0;
}
