#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){

    int fd1 = open("myfile1",O_WRONLY|O_TRUNC|O_CREAT,0666);
    int fd2 = open("myfile2",O_WRONLY|O_TRUNC|O_CREAT,0666);
    int fd3 = open("myfile3",O_WRONLY|O_TRUNC|O_CREAT,0666);
    int fd4 = open("myfile4",O_WRONLY|O_TRUNC|O_CREAT,0666);
    int fd5 = open("myfile5",O_WRONLY|O_TRUNC|O_CREAT,0666);

    printf("%d\n",stdin->_fileno);
    printf("%d\n",stdout->_fileno);
    printf("%d\n",stderr->_fileno);
    printf("%d\n",fd1);
    printf("%d\n",fd2);
    printf("%d\n",fd3);
    printf("%d\n",fd4);
    printf("%d\n",fd5);
    
    //int fd = open("myfile",O_WRONLY|O_TRUNC|O_CREAT,0666);
    
    //const char* msg = "hello write\n";
    //write(fd,msg,strlen(msg));
    
    //close(fd);
    
    
    //int fd = open("myfile",O_RDONLY);
    //printf("%d\n",fd);   
    //char buff[64];    
    //const char* msg = "hello write\n";
    //
    //read(fd,buff,strlen(msg));
    //printf("%s",buff);
    //
    //close(fd);

    return 0;
}
