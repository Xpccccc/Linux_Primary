#include "mystdio.h"
#include <string.h>
#include <unistd.h>

int main(){
    myFILE* fp = my_fopen("myfile","w");
    
    if(!fp) return 1;

    const char* msg = "hello my_fwrite\n";

    my_fwrite(msg,strlen(msg),fp);

    //int cnt = 5;
    //char buffer[64];
    //while(cnt)
    //{
    //    snprintf(buffer, sizeof(buffer), "helloworld,hellobit,%d  ", cnt--);
    //    my_fwrite( buffer, strlen(buffer),fp);
    //    DebugPrint(fp);
    //    sleep(2);
    //    //my_fflush(fp);
    //}
    //
    //fork();

    my_fclose(fp);
    return 0;
}
