#include <stdio.h>

int main(){
    int chisla[1000000];
    int k, arr_size;
    int curr_sum = 0;
    
    scanf("%d", &arr_size);
    for (int i=0; i<arr_size; ++i){
        scanf("%d", &chisla[i]);
    }
    
    scanf("%d", &k);
    for (int i=0; i<k; ++i){
        curr_sum += chisla[i];
    }
    int max_sum = curr_sum;
    
    for (int i=k; i<arr_size; ++i){
        curr_sum = curr_sum + chisla[i] - chisla[i-k];
        if (curr_sum>max_sum){
            max_sum = curr_sum;
        }
    }
    
    printf("%d", max_sum);
}