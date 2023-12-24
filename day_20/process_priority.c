#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    
    while(1){
        printf("I am a process~ pid: %d, ppid: %d \n",getpid(),getppid());
    }
    return 0;
}
