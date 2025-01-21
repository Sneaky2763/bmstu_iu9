#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b){
    int let_a=0;
    int let_b=0;
    char *str1=(char *) a;
    char *str2=(char *) b;
    
    for(int i = 0; str1[i]!='\0'; i++){
        if (str1[i] == 'a'){
            ++let_a;    
        }
    }
    for(int i = 0; str2[i]!='\0'; i++){
        if (str2[i] == 'a'){
            ++let_b;    
        }
    }

    if(let_a<let_b){
        return -1;
    } else if(let_a==let_b){
        return 0;
    }
    return 1;
}

void swap(void *base, int i, int j, int width){
    char swapper;
    char *str1=(char *)base+width*i;
    char *str2=(char *)base+width*j;
    for(int i=0; i<width; ++i){
        swapper=*str1;
        *str1=*str2;
        *str2=swapper;
        ++str1;
        ++str2;
    }
}

void heapify(void *base, int i, size_t nel, size_t width, int (*compare)(const void *a, const void *b)){

    while(1){
        int l=2*i+1;
        int r=l+1;
        int j=i;
        if (l<nel && compare((char*)base+width*i,(char*)base+width*l)<0){
            i=l;
        }
        if(r<nel && compare((char*)base+width*i,(char*)base+width*r)<0){
            i=r;
        }
        if(i==j){
            break;
        }
        swap(base, i, j, width);
    }
}

void buildheap(void *base, size_t nel, size_t width, int (*compare)(const void *a, const void *b)){
    int i=nel/2-1;
    while(i>=0){
        heapify(base, i, nel, width, compare);
        --i;
    }
}

void hsort(void *base, size_t nel, size_t width, int (*compare)(const void *a, const void *b)){
    buildheap(base, nel, width, compare);
    int i=nel-1;

    while(i>0){
        swap(base, 0, i, width);
        heapify(base, 0, i, width, compare);
        --i;
    }
}

int main(){
    int n;
    scanf("%d ", &n);

    char strings[n][1001];
    for(int i = 0; i < n; ++i){
        fgets(strings[i], 1000*sizeof(char), stdin);
    }

    hsort(strings, n, 1001, compare);

    for(int i=0; i<n; ++i){
        printf("%s", strings[i]);
    }
    return 0;
}