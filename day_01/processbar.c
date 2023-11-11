#include "processbar.h"

const char *lable="|/-\\";

void process(double rt){
    static int num = 0;
    static char bar[101] = {0}; 
    printf("[\033[0;32m%-100s\033[0m]][%5.1f%%][%c]\r", bar, rt, lable[num%4]);
    ++num;
    fflush(stdout);
    bar[(int)rt] = '#';
    if((int)rt == 100) printf("\n");
}
