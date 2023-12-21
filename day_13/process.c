#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
     int ret = fork();
     if(0 == ret){
         while(1){

            printf("I am child process : id: %d!, ret: %d\n", getpid(), ret);
            sleep(1);
         }
     }else if(ret > 0){
         while(1){

            printf("I am father process : id: %d!, ret: %d\n", getpid(), ret);
            sleep(1);
         }
     }

     return 0;
}
