#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date {
    int Day, Month, Year;
};

int key(struct Date element, int curr_stage){
    if(curr_stage==2){
        return element.Day-1;
    }
    if(curr_stage==1){
        return element.Month-1;
    }
    return element.Year-1970;
}

int count_size(int curr_stage){
    if(curr_stage==2){
        return 31;
    }
    if(curr_stage==1){
        return 12;
    }
    return 61;
}

void distributionsort(int (*key)(struct Date element, int curr_stage),
    int curr_stage, struct Date *s, int n, int index, struct Date *res){
    
    int size=count_size(curr_stage);
    int count[size];
    for(int i=0; i<size; ++i){
        count[i]=0;
    }
    
    int j=0;
    int k;
    while(j<n){
        k=key(s[j], curr_stage);
        ++count[k];
        ++j;
    }
    
    int i=1;
    while(i<size){
        count[i]+=count[i-1];
        ++i;
    }

    j=n-1;
    while(j>=0){
        k=key(s[j], curr_stage);
        i=count[k]-1;
        count[k]=i;
        res[i]=s[j];
        --j;
    }

}

void radixsort(int curr_stage, struct Date *dates, int n){
    struct Date d[n];
    struct Date res[n];
    for(int i=0; i<n; ++i){
        d[i]=dates[i];
    }

    while(curr_stage>=0){
        for(int u=0; u<n; ++u){
            distributionsort(key, curr_stage, d, n, u, res);
            memcpy(d, res, n*sizeof(struct Date));
        }
        --curr_stage;
    }
    for(int i=0; i<n; ++i){
        printf("%04d %02d %02d\n", d[i].Year, d[i].Month, d[i].Day);
    }
}

int main(){
    int n;
    scanf("%d", &n);

    struct Date dates[n];
    for(int i=0; i<n; ++i){
        scanf("%d %d %d", &dates[i].Year, &dates[i].Month, &dates[i].Day);
    }

    radixsort(2, dates, n);

    return 0;
}