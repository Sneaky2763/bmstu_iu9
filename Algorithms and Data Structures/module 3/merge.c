#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem{
    int val;
    int key;
} elem;

typedef struct PriorityQueue{
    elem *heap;
    int cap;
    int count;
} PriorityQueue;

void swap(elem *a, elem *b){
    elem swapper;
    swapper=*a;
    *a=*b;
    *b=swapper;
}

void InitPriorityQueue(PriorityQueue *q, int n){
    q->heap=(elem *)malloc(sizeof(elem)*n);
    q->cap=n;
    q->count=0;
}

void Insert(PriorityQueue *q, elem ptr){
    int i=q->count;
    if (i==q->cap){
        return;
    }
    q->count++;
    q->heap[i]=ptr;
    while(i>0 && q->heap[(i-1)/2].key>q->heap[i].key){
        swap(&q->heap[(i-1)/2], &q->heap[i]);
        i=(i-1)/2;
    }
}

void Heapify(int i, int n, PriorityQueue *q){
	while(1){
        int l=2*i+1;
        int r=l+1;
        int j=i;
        if (l<n && q->heap[i].key>q->heap[l].key){
            i=l;
        }
        if(r<n && q->heap[i].key>q->heap[r].key){
            i=r;
        }
        if(i==j){
            break;
        }
        swap(&q->heap[i], &q->heap[j]);
    }
}

elem ExtractMin(PriorityQueue *q){
    if(q->count==0){
        printf("no elements");
    }
    elem ptr=q->heap[0];
    q->count--;
    if(q->count>0){
        q->heap[0]=q->heap[q->count];
        Heapify(0, q->count, q);
    }
    return ptr;
}

void Merge(PriorityQueue *q, int amount, int *size, elem **arr, int *res) {
    for (int i=0; i<amount; ++i) {
        if (size[i]>0) {
            Insert(q, arr[i][0]);
            ++arr[i];
            --size[i];
        }
    }

    int pos=0;
    while (q->count>0) {
        elem minElem=ExtractMin(q);
        res[pos]=minElem.key;
        ++pos;

        int curr_arr=minElem.val;
        if (size[curr_arr]>0) {
            Insert(q, arr[curr_arr][0]);
            ++arr[curr_arr];
            --size[curr_arr];
        }
    }
}

int main(){
    int k;
    scanf("%d", &k);
    int size[k];
    int free_arrs[k];
    int allelem=0;
    for(int i=0; i<k; ++i){
        scanf("%d", &size[i]);
        free_arrs[i]=size[i];
        allelem+=size[i];
    }

    elem *arr[k];
    for(int i=0; i<k; ++i){
        arr[i]=(elem *)malloc(sizeof(elem)*size[i]);
        for(int j=0; j<size[i]; ++j){
            scanf("%d", &arr[i][j].key);
			arr[i][j].val=i;
        }
    }

    int *res=(int *)malloc(sizeof(int)*allelem);
    PriorityQueue q;
    InitPriorityQueue(&q, k);
    Merge(&q, k, size, arr, res);

    for(int i=0; i<allelem; ++i){
        printf("%d ", res[i]);
    }

    for(int i=0; i<k; ++i){
        arr[i]-=free_arrs[i];
        free(arr[i]);
    }
    free(res);
    free(q.heap);
    return 0;
}