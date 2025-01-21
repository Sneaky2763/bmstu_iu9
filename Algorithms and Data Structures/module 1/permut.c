#include <stdio.h>

int is_gettable = 0;

void swap(int *a, int *b){
    int swapper = *a;
    *a = *b;
    *b = swapper;
}

void permut(int arr_perm[], int arr_comp[], int i, int n){
    int equal = 1;
    if (i == n){
        for (int k=0; k<8; ++k){
            if(arr_perm[k]!=arr_comp[k]){
                equal = 0;
            }
        }
        if (equal){
            is_gettable = 1;
        }
    } else {
       for (int j = i; j < n; ++j){
          swap(&arr_perm[i], &arr_perm[j]);          
          permut(arr_perm, arr_comp, i+1, n);
          swap(&arr_perm[i], &arr_perm[j]); 
       }
   }
} 


int main(){
    int arr_1[8];
    int arr_2[8];
    
    for(int i=0; i<8; ++i){
        scanf("%d", &arr_1[i]);
    }
    for(int i=0; i<8; ++i){
        scanf("%d", &arr_2[i]);
    }
    
    permut(arr_1, arr_2, 0, 8);

    if (is_gettable){
        printf("yes");
        return 0;
    }
    
    printf("no");
    return 0;
}
