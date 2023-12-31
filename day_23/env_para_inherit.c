#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    extern char **environ;
    char str[] = "HELLO=aaaaaaaaaaaaa";
    putenv(str);
    setenv("BYEBYE","bbbbbbbbbbbbb",1);
    printf("%s\n",getenv("PATH"));
    printf("%s\n",getenv("HELLO"));
    printf("%s\n",getenv("BYEBYE"));
    int i = 0;
    for(; environ[i]; ++i){
        printf("%s\n",environ[i]);
    }
    pid_t id = fork();
    if(0 == id){
        printf("我是子进程\n");
        printf("%s\n",getenv("HELLO"));
        printf("%s\n",getenv("BYEBYE"));
        int i = 0;
        for(; environ[i]; ++i){
            printf("%s\n",environ[i]);
        }
    }
    return 0;
}
