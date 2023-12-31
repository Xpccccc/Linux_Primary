#include <stdio.h>
#include <stdlib.h>

int main(){
    char* ret = getenv("MYENV");
    if(ret){
        printf("%s\n",ret);
    }
    return 0;
}
