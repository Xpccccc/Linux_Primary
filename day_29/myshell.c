#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1024
#define MAX_LEN 128
#define SEP " "

char* argv[MAX_LEN];//命令行字符串数组
char pwd[SIZE];
char envtemp[SIZE];
int lastcode = 0;//退出码

const char* HostName(){
    char* hostname = getenv("HOSTNAME");
    if(hostname) return hostname;
    else return "None";
}

const char* UserName(){
    char* hostname = getenv("USER");
    if(hostname) return hostname;
    else return "None";
}

const char* CurrentWorkDir(){
    char* hostname = getenv("PWD");
    if(hostname) return hostname;
    else return "None";
}

char* Home(){
    char* hostname = getenv("HOME");
    if(hostname) return hostname;
    else return "None"; 
}

int Interactive(char* commandline, int size){
    printf("[%s@%s %s]$ ",UserName(),HostName(),CurrentWorkDir());
    fgets(commandline,SIZE,stdin);
    commandline[strlen(commandline)-1] = '\0';
    
    return strlen(commandline);//空串返回0
}

void Split(char* commandline){
    int i = 0;
    argv[i++] = strtok(commandline,SEP);
    while(argv[i++] = strtok(NULL,SEP));
    //解决ls无彩色问题
    if(strcmp(argv[0],"ls") == 0){
        argv[i-1] = (char*)"--color";
        argv[i] = NULL;
    }
}

int BuildingCmd(){
    int ret = 0;
    if(strcmp(argv[0],"cd") == 0){
        ret = 1;
        char* target = argv[1];
        //cd XXX 和cd
        if(!target) target = Home();//第二个参数为NULL
        //改变当前工作目录
        chdir(target);
        //处理target为..的情况
        //重新获取当前路径
        char temp[1024];
        getcwd(temp,1024);
        //更新当前环境变量PWD
        snprintf(pwd,SIZE,"PWD=%s",temp);
        //导出环境变量
        putenv(pwd);
    }
    else if(strcmp(argv[0],"export") == 0){
        ret = 1;
        if(argv[1]){
            strcpy(envtemp,argv[1]);
            putenv(envtemp);
        }
    }
    else if(strcmp(argv[0],"echo") == 0){
        ret = 1;
        if(argv[1] == NULL){
            printf("\n");
        }else{
            if(argv[1][0] == '$'){
                if(argv[1][1] == '?'){
                    printf("%d\n",lastcode);
                    lastcode = 0;
                }else{
                    char* e = getenv(argv[1]+1);
                    if(e) printf("%s\n",e);
                }
            }
            else{
                printf("%s\n",argv[1]);
            }
        }
    }
    return ret;
}

void Execute(){
    //只能交给子进程，如果用父进程执行命令行，执行一次就结束了
    pid_t id = fork();
    if(id < 0) perror("fork\n");
    else if(id == 0){
        execvp(argv[0],argv);
        exit(1);//执行完退出
    }
    //父进程等待子进程
    int status = 0;
    pid_t rid = waitpid(id,&status,0);
    if(rid == id) lastcode = WEXITSTATUS(status);//等待成功
}

int main(){

    while(1){
        char commandline[SIZE];
        //1. 打印命令行提示符，获取用户的命令字符串
        int n = Interactive(commandline,SIZE);
        if(!n) continue;//返回值为0就是空串，下面代码不再执行
        //2. 对命令行字符串进行切割
        Split(commandline);
        //3. 处理内建命令
        n = BuildingCmd();
        if(n) continue;
        //4. 执行这个命令
        Execute();
    }
    //int i;
    //for(i=0;argv[i];++i){
    //    printf("argv[%d]:%s\n",i,argv[i]);
    //}
    return 0;
}
