#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
    int n;
    scanf("%d", &n);
    
    double num[n];
    float numer, denom;
    for(int i=0; i<n; ++i){
        scanf("%d/%d", &numer, &denom);
        num[i]=numer/denom;
    }

    int l=0;
    int l_best=0;
    int r_best=0;
    float curr_prod_rank=0;
    float best_prod_rank=log2(num[0]);
    for(int r=0; r<n; ++r){
        curr_prod_rank+=log2(num[r]);
        if(curr_prod_rank>best_prod_rank){
            best_prod_rank=curr_prod_rank;
            l_best=l;
            r_best=r;
        }
        if(curr_prod_rank<0){
            l=r+1;
            curr_prod_rank=0;
        }
    }
    printf("%d %d", l_best, r_best);
    return 0;
}