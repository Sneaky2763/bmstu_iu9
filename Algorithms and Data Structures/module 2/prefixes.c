#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prefix(char *s){
    int len=strlen(s);
    int pref[len];
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

    for(int i=1; i<len; ++i) {
        int preflen=i+1-pref[i];
        if((i+1)%preflen==0 && pref[i]!=0) {
            printf("%d %d\n", i+1, (i+1)/preflen);
        }
    }
}

int main(int argc, char **argv){
    prefix(argv[1]);
    return 0;
}