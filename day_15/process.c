#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    printf("马上准备创建子进程\n");
    pid_t id =  fork();
    if(id < 0) perror("fork error\n");
    else if(id == 0) {
        //子进程
        int cnt = 10; 
        while(cnt){
            printf("I am child ,pid: %d ,ppid: %d\n",getpid(),getppid());
            sleep(1);
            cnt--;
        }
    }
    else{
        //父进程
        int cnt = 5;
        while(cnt){
            printf("I am father ,pid: %d ,ppid: %d\n",getpid(),getppid());
            sleep(1);
            cnt--;
        }
    }
    return 0;
}
