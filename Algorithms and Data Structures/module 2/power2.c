#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count=0;

void comb_rec(int *num, int *res, int start, int arr_len, int curr, int m);

void comb(int *num, int m, int len){
    int res[m];
    comb_rec(num, res, 0, len, 0, m);
}

void comb_rec(int *num, int *res, int start, int arr_len, int curr, int m){
    if (curr==m){
        int sum=0;
        for(int i=0; i<m; ++i){
            sum+=res[i];
        }
        int check=(sum&(sum-1));
        if (check==0 && sum!=0){
            count++;
        }
        return;
    } else {
        if(arr_len-start>=m-curr){
            for(int i=start; i<arr_len; ++i){
                res[curr]=num[i];
                comb_rec(num, res, i+1, arr_len, curr+1, m);
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int num[n];
    for(int i=0; i<n; ++i){
        scanf("%d", &num[i]);
    }
    for(int i=1; i<=n; ++i){
        comb(num, i, n);
    }
    printf("%d", count);
    return 0;
}