#include "processbar.h"                                 

#define FILESIZE (1024*1024*1024)

void downlode(callback_t cb) {
    srand(time(NULL) ^ 1023);
    long total = FILESIZE;
    while (total) {
        usleep(100000);//下载动作
        long one = rand() % (1024 * 1024 * 5);
        total -= one;
        if (total < 0) total = 0;

        //当前进度
        double rate = ((FILESIZE - total) * 1.0) * 100 / FILESIZE;
//        printf("%.1f\n", rate);
        cb(rate);
    }
}

int main() {
    downlode(process);
    return 0;
}
