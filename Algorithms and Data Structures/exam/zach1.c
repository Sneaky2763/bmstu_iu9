#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long mingle(int a, int b){
    int a_16[16]={ 0 };
    int b_16[16]={ 0 };

    for(int i=15; i>=0; --i){
        a_16[i]=a%2;
        a/=2;
    }
    for(int i=15; i>=0; --i){
        b_16[i]=b%2;
        b/=2;
    }

    int cher[32]={ 0 };
    for(int i=0; i<32; ++i){
        if(i%2==0){
            cher[i]=a_16[i/2];
        } else {
            cher[i]=b_16[i/2];
        }
    }

    long long res=0;
    long long pow=1;
    for(int i=31; i>=0; --i){
        res+=cher[i]*pow;
        pow*=2;
    }
    return res;
}

long long sel(long long a, long long b){
    int a_32[32]={ 0 };
    int b_32[32]={ 0 };

    for(int i=31; i>=0; --i){
        a_32[i]=a%2;
        a/=2;
    }
    for(int i=31; i>=0; --i){
        b_32[i]=b%2;
        b/=2;
    }

    long long res=0;
    for(int i=0; i<32; ++i){
        if(b_32[i]==1){
            res*=2;
            res+=a_32[i];
        }
    }
    return res;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        long long a;
        char oper;
        long long b;
        scanf("%lld %c %lld", &a, &oper, &b);

        if(oper=='$'){
            printf("%lld\n", mingle(a, b));
        }
        if(oper=='~'){
            printf("%lld\n", sel(a, b));
        }
    }
    return 0;
}