#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    printf("当前进程id：%d,当前进程的父进程id：%d\n",getpid(),getppid());
    return 0;
}
