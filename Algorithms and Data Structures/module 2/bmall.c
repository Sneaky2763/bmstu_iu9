#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delta1(char *s, int size, int *table){
    int len=strlen(s);
    for(int i=0; i<size; ++i){
        table[i]=len;
    }
    for(int j=0; j<len; ++j){
        table[s[j]]=len-j-1;
    }
}

void suffix(char *s, int *sigma){
    int len=strlen(s);
    int t=len-1;
    sigma[len-1]=t;
    int i=len-2;

    while(i>=0){
        while(t<len-1 && s[t]!=s[i]){
            t=sigma[t+1];
        }
        if(s[t]==s[i]){
            --t;
        }
        sigma[i]=t;
        --i;
    }
}

void delta2(char *s, int *table2){
    int len=strlen(s);
    int sigma[len];
    suffix(s, sigma);

    int i=0;
    int t=sigma[0];
    while(i<len){
        while(t<i){
            t=sigma[t+1];
        }
        table2[i]=-i+t+len;
        ++i;
    }
    i=0;
    while(i<len-1){
        t=i;
        while(t<len-1){
            t=sigma[t+1];
            if(s[i]!=s[t]){
                table2[t]=-(i+1)+len;
            }
        }
        ++i;
    }
}

void bmsubst(char *s, int size, char *t){
    int table[size];
    delta1(s, size, table);
    
    int s_len=strlen(s);
    int t_len=strlen(t);

    int table2[s_len];
    delta2(s, table2);

    int k=s_len-1;

    while(k<t_len){
        int i=s_len-1;
        int pos=k;
        while(i>0 && t[pos]==s[i]){
            --i;
            --pos;
        }
        if(i==0 && t[pos]==s[i]){
            printf("%d ", pos);
        }
        if(table[t[k]]>table2[i]){
            k+=table[t[k]];
        } else {
            k+=table2[i];
        }
    }
}

int main(int argc, char **argv){
    int size=127;
    char *s=argv[1];
    char *t=argv[2];
    bmsubst(s, size, t);
    return 0;
}
