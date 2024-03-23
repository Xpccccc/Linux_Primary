#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){
    
    //int fd  = open("myfile",O_RDWR|O_CREAT|O_TRUNC,0666);

    const char* msg1 = "hello printf\n"; // \n自带刷新
    const char* msg2 = "hello fwrite\n";
    const char* msg3 = "hello write\n";
    
    write(1,msg3,strlen(msg3));
    printf("%s",msg1);
    fwrite(msg2,strlen(msg2),1,stdout);
    
    fork();
    return 0;
}
