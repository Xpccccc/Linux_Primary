#include <stdio.h>
#include <string.h>

int main(){

    //FILE* pf = fopen("myfile","r");
    //if(!pf){
    //    perror("fopen");
    //    return 1;
    //}

    char buffer[10];
    // 这里要注意，这里的sizeof(buffer)-1是多少，fread就会去读多少数据，直到读到这么多数据
    size_t bytesRead = fread(buffer, sizeof(char), sizeof(buffer)-1, stdin);
    buffer[bytesRead] = '\0';  // 字符串结束符
    printf("buff:%s",buffer);

    //fprintf(pf,"%s",msg);
        
    //fwrite(msg,strlen(msg),1,stdout);
    //FILE* pf = fopen("myfile","r");
    //if(!pf){
    //    perror("fopen error");
    //    return 1;
    //}

    //int in = 0;
    //fscanf(pf,"%d",&in);
    //printf("%d\n",in);

    //fclose(pf);
    return 0;
}
