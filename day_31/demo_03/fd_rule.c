#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

    //close(0);
    close(1);
    //close(2);

    //int fd = open("myfile",O_RDONLY);
    int fd = open("myfile",O_WRONLY|O_CREAT,0666);

    if(fd < 0){
        perror("open");
        return 1;
    }

    printf("%d\n",fd);
    fflush(stdout);// 刷新缓冲区
    close(fd);
    return 0;
}
