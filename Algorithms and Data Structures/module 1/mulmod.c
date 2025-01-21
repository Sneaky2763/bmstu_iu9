#include <stdio.h>

int main(){
    unsigned long long a, b, m;
    unsigned long long ans = 0;
    scanf("%llu %llu %llu", &a, &b, &m);
    
    int digits[64];
    
    
    for (int i=63; i>-1; --i){
        digits[i]=b%2;
        b/=2;
    }
    
    for (int i=0; i<64; ++i){
        ans += (a*digits[i])%m;
        if (i < 63){
            ans = (ans%m)*2;
        }
        ans%=m;
    }
    
    printf("%llu", ans);
}
