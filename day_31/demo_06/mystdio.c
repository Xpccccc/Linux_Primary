#include "mystdio.h"
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

myFILE* my_fopen(const char *path, const char *mode){
    int flag = 0;
    if(strcmp(mode,"r") == 0){
        flag |= O_RDONLY;
    }else if(strcmp(mode,"w") == 0){
        flag |= (O_WRONLY|O_CREAT|O_TRUNC);
    }else if(strcmp(mode,"a") == 0){
        flag |= (O_WRONLY|O_CREAT|O_APPEND);
    }else{
        return NULL;
    }

    int fd = 0;
    if(flag & O_WRONLY){
        umask(0);
        fd = open(path,flag,0666);
    }else{
        fd = open(path,flag);
    }

    if(fd < 0) return NULL;

    myFILE* fp = (myFILE*)malloc(sizeof(myFILE));
    if(!fp){
        perror("malloc");
        return NULL;
    }

    fp->fileno = fd;
    fp->pos = 0;
    fp->cap = SIZE;
    fp->flush_mode = LINE_FLUSH;

    return fp;
}

void my_fflush(myFILE* stream){
    if(stream->pos == 0) return;
    write(stream->fileno,stream->buff,stream->pos);
    stream->pos = 0;// 刷新后pos到最初位置
}

int my_fwrite(const char *ptr, int size,myFILE *stream){
    memcpy(stream->buff+stream->pos,ptr,size);// buff从pos开始 
    stream->pos += size;
    if((stream->flush_mode & LINE_FLUSH) && (stream->buff[stream->pos-1] == '\n')){
        my_fflush(stream);
    }else if((stream->flush_mode & FULL_FLUSH) && (stream->pos == stream->cap)){
        my_fflush(stream);
    }

    return size;
}

void my_fclose(myFILE* stream){
    my_fflush(stream);
    close(stream->fileno);
    free(stream);
}

const char *toString(int flag)
{
    if(flag & NONE_FLUSH) return "None";
    else if(flag & LINE_FLUSH) return "Line";
    else if(flag & FULL_FLUSH) return "FULL";
    return "Unknow";
}

void DebugPrint(myFILE *fp)
{
    printf("outbufer: %s\n", fp->buff);
    printf("fd: %d\n", fp->fileno);
    printf("pos: %d\n", fp->pos);
    printf("cap: %d\n", fp->cap);
    printf("flush_mode: %s\n", toString(fp->flush_mode));
}
