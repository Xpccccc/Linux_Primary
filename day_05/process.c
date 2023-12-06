#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    printf("mypid = %d\n",getpid());
    printf("更改工作目录前\n");
    sleep(20);

    chdir("/home/xp2");
    printf("更改工作目录后\n");
    sleep(10);

    FILE* pf = fopen("110.txt","w");
    if(pf == NULL) return 1;

    fclose(pf);
    pf = NULL;

    printf("新建文件完成\n");
    sleep(30);
    //while(1){
    //    printf("I am a process~,mypid = %d ,myppid = %d\n",getpid(),getppid());
    //    sleep(1);
    //}
    return 0;
}
