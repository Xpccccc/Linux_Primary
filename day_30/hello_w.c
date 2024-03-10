#include <stdio.h>
#include <string.h>

int main(){
    FILE* pf = fopen("myfile.txt","w");
    if(!pf){
        perror("fopen");
        return 1;
    }

    const char* msg = "hello fopen\n";
    int count = 5;
    while(count--){
        fwrite(msg,strlen(msg),1,pf);
    }
    
    fclose(pf);
    return 0;
}
