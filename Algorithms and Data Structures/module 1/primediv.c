#include <stdio.h>

int main(){
    int size=65538;
    int resheto[size];
    
    for (int i=0; i<size; ++i){
        resheto[i]=1;
    }
    
    for (int i=2; i<size; ++i) {
        if (resheto[i]==1) {
            for (unsigned int j=i*i; j<size; j+=i){
                resheto[j]=0;
            }
        }
    }
    
    long long x;
    int ans=1;
    
    scanf("%lld", &x);
    
    if(x<0){
        x=-x;
    }
    
    for (int i=2; i<size; ++i){
        if(resheto[i]){
            while(x%i==0){
                x/=i;
                ans=i;
            }
        }
    }
    if(x>ans){
        ans=x;
    }
    
    printf("%d", ans);
    return 0;
}