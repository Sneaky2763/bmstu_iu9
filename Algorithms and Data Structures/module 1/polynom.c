#include <stdio.h>

int main(){
    long long n, size, x0;
    long long ans = 0;
    long long dans = 0;
    scanf("%lld %lld", &n, &x0);
    size=n+1;
    
    long long koef[size];
    for (int i=0; i<size; ++i){
        scanf("%lld", &koef[i]);
    }
    
    for (int i=0; i<size; ++i){
        ans+=koef[i];
        if (i < n){
            ans*=x0;   
        }
    }
    
    for (int i=0; i<size-1; ++i){
        dans+=koef[i]*(n-i);
        if (i < n-1){
            dans*=x0;   
        }
    }
    
    printf("%lld %lld\n", ans, dans);
    return 0;
}
