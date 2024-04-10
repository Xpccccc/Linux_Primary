#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>


void writer(int wfd){
    const char* msg = "hello father";
    char buff[128];
    pid_t pid  = getpid();
    int cnt = 0;
    while(1){
        snprintf(buff,sizeof(buff),"sent message: %s :%d,pid: %d\n",msg,cnt,pid);
        write(wfd,buff,strlen(buff)+1);
        cnt++;
        sleep(1);
    }
}

void reader(int rfd){
    char buff[1024];
    while(1){
        ssize_t n = read(rfd,buff,sizeof(buff)-1);
        printf("get message: %s",buff);
    }

}


int main(){
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1)
        return -1;
    
    printf("pipefd[0]:%d,pipefd[1]:%d\n",pipefd[0],pipefd[1]);

    pid_t id = fork();
    if(id == 0){
        close(pipefd[0]);
        // w
        writer(pipefd[1]);
        exit(10);
    }
    // 父进程
    close(pipefd[1]);
    reader(pipefd[0]);

    wait(NULL);
    return 0;
}
