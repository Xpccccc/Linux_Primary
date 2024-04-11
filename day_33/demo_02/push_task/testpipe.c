#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int pipefd[2];
    int n = pipe(pipefd);

    pid_t id = fork(); 
    if(id == 0){
        //child -- r
        close(pipefd[1]);
        char buff[128];
        ssize_t n = read(pipefd[0],buff,sizeof(buff));
        printf("%s",buff);
        exit(0);
    }

    // father -- w
    close(pipefd[0]);
    const char* msg = "i am father\n";
    write(pipefd[1],msg,strlen(msg));

    wait(NULL);
    return 0;
}