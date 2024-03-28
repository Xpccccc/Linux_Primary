#include <stdio.h>
#include "cal.h"
#include "mystdio.h"

int main(){
    int res = Add(10,20);
    printf("%d+%d=%d\n",10,20,res);

    myFILE* fp = my_fopen("log1.txt","w");
    if(fp) return 1;
    return 0;
}
