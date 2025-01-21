#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem{
    int start;
    int dur;
    int end;
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
    while(i>0 && q->heap[(i-1)/2].end>q->heap[i].end){
        swap(&q->heap[(i-1)/2], &q->heap[i]);
        i=(i-1)/2;
    }
}

void Heapify(int i, int n, PriorityQueue *q){
    while(1){
        int l=2*i+1;
        int r=l+1;
        int j=i;
        if (l<n && q->heap[i].end>q->heap[l].end){
            i=l;
        }
        if(r<n && q->heap[i].end>q->heap[r].end){
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

int main(){
    int n;
    scanf("%d", &n);
    PriorityQueue q;
    InitPriorityQueue(&q, n);

    int m;
    scanf("%d", &m);
    int allelem=0;
    elem arr[m];
    for(int i=0; i<m; ++i){
        scanf("%d %d", &arr[i].start, &arr[i].dur);
		arr[i].end=arr[i].start+arr[i].dur;
        if(i<n){
            Insert(&q, arr[i]);
        }
    }

    int res=0;
    int i;
    for(i=n; i<m; ++i){
        res=ExtractMin(&q).end;
        if(arr[i].start>res){
            arr[i].end=arr[i].start+arr[i].dur;
        } else {
            arr[i].end=res+arr[i].dur;
        }
        Insert(&q, arr[i]);
    }

    for(int i=0; i<n; ++i){
        if(i<m && q.heap[i].end>res){
            res=q.heap[i].end;
        }
    }
    printf("%d", res);
    free(q.heap);
    return 0;
}