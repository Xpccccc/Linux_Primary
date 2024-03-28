#include<stdio.h>

#define NONE_FLUSH (1<<1)
#define LINE_FLUSH (1<<2)
#define FULL_FLUSH (1<<3)
#define SIZE 1024

typedef struct _myFILE{
    int fileno;
    int pos;// 当前写入位置
    int cap;// 文件容量
    int flush_mode; // 刷新模式
    char buff[SIZE];
}myFILE;

myFILE* my_fopen(const char *path, const char *mode);

int my_fwrite(const char *ptr, int size,myFILE *stream);

//int my_fread(void *ptr, int size, myFILE *stream);

void my_fclose(myFILE* stream);

const char *toString(int flag);

void DebugPrint(myFILE *fp);
