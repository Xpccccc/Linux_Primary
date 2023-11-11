#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

//函数指针
typedef void(*callback_t)(double);

//进度条
void process(double rt);
