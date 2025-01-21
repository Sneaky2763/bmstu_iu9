#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selectionsort(int low, int high, int *num){
    for(int i=low; i<=high; ++i){
        int minindex=i;
        for(int j=i+1; j<=high; ++j){
            if (num[j]<num[minindex]){
                minindex=j;
            }
        }
        int swapper=num[i];
        num[i]=num[minindex];
        num[minindex]=swapper;
    }
}

int partition(int low, int high, int *num){
    int i=low;
    int j=low;
    while(j<high){
        if (num[j]<num[high]){
            int swapper=num[j];
            num[j]=num[i];
            num[i]=swapper;
            ++i;
        }
        ++j;
    }
    int swapper=num[i];
    num[i]=num[high];
    num[high]=swapper;
    return i;
}

void quicksortrec(int low, int high, int *num, int m);

void quicksort(int n, int *num, int m){
    quicksortrec(0, n-1, num, m);
}

void quicksortrec(int low, int high, int *num, int m){
    while(high-low>=m){
        int q=partition(low, high, num);
            if(q-low<high-q){
                quicksortrec(low, q-1, num, m);
                low=q+1;
            } else {
                quicksortrec(q+1, high, num, m);
                high=q-1;
            }
    }
    if(high-low<m && high-low>0){
        selectionsort(low, high, num);
    } 
}

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);

    int num[n];
    for(int i=0; i<n; ++i){
        scanf("%d", &num[i]);
    }

    quicksort(n, num, m);

    for(int i=0; i<n; ++i){
        printf("%d ", num[i]);
    }
    return 0;
}