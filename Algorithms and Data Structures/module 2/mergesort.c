#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(int a, int b){
    if (abs(a)<abs(b)){
        return -1;
    }
    return 1;
}
void insertionsort(int low, int high, int *num, int (*compare)(int a, int b)){
    for(int i=low; i<high; ++i){
        for(int j=low+1; j<=high; ++j){
            if(compare(num[j], num[j-1])==-1){
                int swapper=num[j];
                num[j]=num[j-1];
                num[j-1]=swapper;
            }
        }
    }
}
void merge(int k, int l, int m, int *num, int (*compare)(int a, int b)){
    int res[m-k+1];
    int i=k;
    int j=l+1;
    int h=0;
    while(h<m-k+1){
        if(j<=m && ( (i==l+1) || (compare(num[j], num[i]))==-1 )){
            res[h]=num[j];
            j++;
        } else{
            res[h]=num[i];
            i++;
        }
        h++;
    }
    for(int a=0; a<h; ++a){
        num[k+a]=res[a];
    }
}

void mergesortrec(int low, int high, int *num);

void mergesort(int n, int *num){
    mergesortrec(0, n-1, num);
}

void mergesortrec(int low, int high, int *num){
    if (low<high){
        if(high-low<5){
            insertionsort(low, high, num, compare);
        } else {
            int mid=(low+high)/2;
            mergesortrec(low, mid, num);
            mergesortrec(mid+1, high, num);
            merge(low, mid, high, num, compare);
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

    mergesort(n, num);
    
    for(int i=0; i<n; ++i){
        printf("%d ", num[i]);
    }
    return 0;
}