#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prefix(char *s, int *pref){
    int len=strlen(s);
    pref[0]=0;
    int t=0;
    for(int i=1; i<len; ++i){
        while(t>0 && s[t]!=s[i]){
            t=pref[t-1];
        }
        if(s[t]==s[i]){
            ++t;
        }
        pref[i]=t;
    }
}

void ispword(char *s, char *t){
    int len=strlen(s);
    int pref[len];
    prefix(s, pref);
    int q=0;
    for(int k=0; k<strlen(t); ++k){
        while(q>0 && s[q]!=t[k]){
            q=pref[q-1];
        }
        if(s[q]==t[k]){
            ++q;
        }
        if(q==0){
            printf("no");
            return;
        }
    }
    printf("yes");
    return;
}

int main(int argc, char **argv){
    char *s=argv[1];
    char *t=argv[2];
    ispword(s, t);
    return 0;
}