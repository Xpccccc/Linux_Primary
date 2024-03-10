#include <stdio.h>
#include <string.h>

int main(){
    FILE* pf = fopen("myfile.txt","r");
    if(!pf){
        perror("fopen");
        return 1;
    }

    char buffer[1024];
    
    const char* msg = "hello xxxxx\n";

    while(1){
        char* r = fgets(buffer,sizeof(msg),pf);
        if(!r)
            break;
        printf("%s",buffer);
    }

    //while(1){
    //    //fgets
    //    // 每次读1个字节，读1024次（文件结束就不读）
    //    size_t s = fread(buffer,1,sizeof(buffer),pf);
    //    if(s > 0){
    //        buffer[s] = 0;
    //        printf("%s",buffer);
    //    }
    //    if(feof(pf)){
    //        break;
    //    }
    //    
    //}
    fclose(pf);
    return 0;
}
