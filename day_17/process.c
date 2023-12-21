#include <stdio.h> 
#include <sys/wait.h>
#include <sys/types.h>    
#include <unistd.h>    
int main()    
{    
     int ret = fork();    
     if(0 == ret){    
         int cnt = 5;
         while(cnt){    
            printf("I am child process : id: %d!, ret: %d\n", getpid(), ret);    
            sleep(1);
            cnt--;
         }
         exit(0);
     }
     //只有父进程才能运行到这里
     pid_t id = wait(NULL);
     int cnt = 10;
     while(cnt){
        printf("I am father process : id: %d!, ret: %d\n", getpid(),ret);    
        sleep(1);
        cnt--;
     }
     printf("等待子进程成功,子进程ID: %d\n",id);
     return 0;    
} 
