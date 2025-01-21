#include <stdio.h>

int main(){
    unsigned long long x;
    scanf("%llu", &x);
    
    unsigned long long fib[92] = {1, 2};
    
    for (int i=2; i<92; ++i){
        fib[i]=fib[i-1]+fib[i-2];
    }
    
    if (x==0){
        printf("0");
        return 0;
    }
    
    int flag = 0;
    for (int i=91; i>-1; i--){
        if (x>=fib[i]){
            printf("1");
            x-=fib[i];
            flag=1;
        }
        else {
            if (flag){
                printf("0");
            }
        }
    }
}
