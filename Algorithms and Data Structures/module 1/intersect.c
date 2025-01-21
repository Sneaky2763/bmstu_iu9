#include <stdio.h>

int main(){
    int len_a, len_b, curr_elem;
    unsigned int a = 0;
    unsigned int b = 0;
    
    scanf("%d", &len_a);
    for (int i=0; i<len_a; ++i){
        scanf("%d", &curr_elem);
        a += (1 << curr_elem);
    }
    
    scanf("%d", &len_b);
    for (int i=0; i<len_b; ++i){
        scanf("%d", &curr_elem);
        b += (1 << curr_elem);
    }
    
    for (int i=0; i<32; i++){
        if (a%2==b%2 && a%2==1){
            printf("%d ", i);
        }
        a/=2;
        b/=2;
        if (a==0 || b==0){
            return 0;
        }
    }
    
    return 0;
}