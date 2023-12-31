#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[], char *env[]) {
    if (argc != 4) {
        printf("usage:\n\t%s -[add|sub|mul|div] x y\n\n", argv[0]);
        return 1;
    }

    int x = atoi((const char*)argv[2]);
    int y = atoi((const char*)argv[3]);
    if (strcmp(argv[1], "-add") == 0) {
        printf("%d+%d = %d\n", x, y, x + y);
    }


    if (strcmp(argv[1], "-sub") == 0) {
        printf("%d-%d = %d\n", x, y, x - y);
    }


    if (strcmp(argv[1], "-mul") == 0) {
        printf("%d*%d = %d\n", x, y, x * y);
    }


    if (strcmp(argv[1], "-div") == 0) {
        printf("%d/%d = %d\n", x, y, x / y);
    }

    return 0;
}




//#include <stdio.h>
//
//int main(int argc, char *argv[]){
//    extern char **environ;
//    int i = 0;
//    for(; environ[i]; i++){
//        printf("%s\n", environ[i]);
//    }
//    return 0;
//}



//#include <stdio.h>
//
//int main(int argc, char *argv[], char *env[]){
//     int i = 0;
//     for(; env[i]; i++){
//        printf("%s\n", env[i]);
//     }
//     return 0;
//}
