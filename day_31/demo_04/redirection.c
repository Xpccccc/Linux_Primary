#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

    int fd = open("myfile",O_RDWR|O_CREAT,0666);
    if(fd < 0){
        perror("open");
        return 1;
    }

    close(1);
    dup2(fd,1);

    printf("hello dup2\n");
    fflush(stdout);
    return 0;
}
