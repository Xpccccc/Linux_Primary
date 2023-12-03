#include <stdio.h>

int Sum(int n){
    int i = 1;
    int sum = 0;
    for(; i<=n; ++i){
        sum += i;
    }
    return sum;
}

int main(){

    int result = Sum(100);
    printf("result = %d\n",result);

    return 0;
}
