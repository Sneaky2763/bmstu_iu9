#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define int unsigned long long
#define char unsigned char

int hash(char *str, int m){
    int r=(int)pow(2, 32);
    int q=2;
    int ans=0;
    for(int i=0; i<m; ++i){
        ans=(ans+str[i]*(int)pow(q, m-i-1))%r;
    }
    return ans;
}
int updatehash(int ht, int t_old, int t_new, int m){
    int r=(int)pow(2, 32);
    int q=2;
    int ans=ht;
    ans=(ans*q+t_new-(t_old*(int)pow(q, m)))%r;
    return ans;
}

void RKSubst(char *s, char *t){
    int len_s=strlen(s);
    int len_t=strlen(t);
    int k=0;
    int hs=hash(s, len_s);
    int ht=0;
    if(len_s>len_t){
        printf("\n");
        return;
    }
    if(len_s<=len_t){
        char slice[len_s];
        for(int i=0; i<len_s; ++i){
            slice[i]=t[i];
        }
        ht=hash(slice, len_s);
    }
    while(k<len_t-len_s+1){
        if(hs==ht){
            int are_equal=1;
            for(int i=k; i<k+len_s; ++i){
                if(t[i]!=s[i-k]){
                    are_equal=0;
                }
            }
            if(are_equal){
                printf("%llu ", k);
            }
        }
        ht=updatehash(ht, t[k], t[k+len_s], len_s);
        ++k;
    }
    k=len_t;
}

int main(int argc, char **argv){
    char *s=argv[1];
    char *t=argv[2];
    RKSubst(s, t);
    return 0;
}