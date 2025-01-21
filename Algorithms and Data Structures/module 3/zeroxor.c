#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prefxor_cnt{
    int prefxor;
    long long cnt;
} prefxor_cnt;

prefxor_cnt xorcnt[100001];

int main(){
    int n;
    scanf("%d", &n);
    int num[n];
    for(int i=0; i<n; ++i){
        scanf("%d", &num[i]);
    }

    int prefxor=0;
    long long cnt=0;

    for(int i=0; i<100001; ++i){
        xorcnt[i].prefxor=-1;
        xorcnt[i].cnt=0;
    }

    for(int i=0; i<n; ++i){
        prefxor=prefxor ^ num[i];
        if(prefxor==0){
            ++cnt;
        }

        int key=abs((prefxor*17929+543)%100001);

        if(xorcnt[key].prefxor==prefxor){
            cnt+=xorcnt[key].cnt;
            xorcnt[key].cnt++;
        }

        if(xorcnt[key].prefxor==-1){
            xorcnt[key].prefxor=prefxor;
            xorcnt[key].cnt=1;
        }

        if(xorcnt[key].prefxor!=prefxor && xorcnt[key].prefxor!=-1){
            while(xorcnt[key].prefxor!=prefxor && xorcnt[key].prefxor!=-1){
                ++key;
                if(key==100001){
                    key=0;
                }
            }
            if(xorcnt[key].prefxor==prefxor){
                cnt+=xorcnt[key].cnt;
                xorcnt[key].cnt++;
            }
            if(xorcnt[key].prefxor==-1){
                xorcnt[key].prefxor=prefxor;
                xorcnt[key].cnt=1;
            }
        }
    }

    printf("%lld", cnt);
    return 0;
}