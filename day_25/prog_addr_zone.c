#include <stdio.h>    
#include <stdlib.h>                                                     
#include <unistd.h>    
    
int g_val = 1;    
int main(){    
    pid_t id = fork();    
    if(id < 0){    
        perror("fork");    
        return 0;    
    }else if(id == 0){
        g_val = 100;
        printf("child[%d]: %d : %p\n", getpid(), g_val, &g_val);    
    }else{    
        printf("parent[%d]: %d : %p\n", getpid(), g_val, &g_val);    
    }    
    return 0;    
}




//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//
//int g_val = 1;
//int main(){
//    pid_t id = fork();
//    if(id < 0){
//		perror("fork");
//		return 0;
//	}else if(id == 0){
//        printf("child[%d]: %d : %p\n", getpid(), g_val, &g_val);
//    }else{
//		printf("parent[%d]: %d : %p\n", getpid(), g_val, &g_val);
//    }
//    return 0;
//}
