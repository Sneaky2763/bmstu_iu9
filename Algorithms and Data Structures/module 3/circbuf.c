#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue{
    int *data;
    int cap;
    int cnt;
    int head;
    int tail;
};

void InitQueue(struct Queue *q, int n){
    q->data=(int *)malloc(sizeof(int)*n);
    q->cap=n;
    q->cnt=0;
    q->head=0;
    q->tail=0;
}

int QueueEmpty(struct Queue *q){
    return (q->cnt==0);
}

void Enqueue(struct Queue *q, int x){
    if(q->cnt==q->cap){
        int *arr=(int *)malloc(sizeof(int)*(q->cap));
        for(int i=0; i<q->cap; ++i){
            arr[i]=q->data[i];
        }
        free(q->data);
        q->cap*=2;
        q->data=(int *)malloc(sizeof(int)*(q->cap));
        for(int i=0; i<q->cap/2; ++i){
            if(i<q->head){
                q->data[i]=arr[i];
            } else {
                q->data[i+q->cap/2]=arr[i];
            }
        }
        q->head+=q->cap/2;
        free(arr);
    }
    q->data[q->tail]=x;
    q->tail++;
    if(q->tail==q->cap){
        q->tail=0;
    }
    q->cnt++;
}

int Dequeue(struct Queue *q){
    if(QueueEmpty(q)){
        printf("no elements");
    }
    int x=q->data[q->head];
    q->head++;
    if(q->head==q->cap){
        q->head=0;
    }
    q->cnt--;
    return x;
}



int main(){
    char input[10];
    scanf("%s", input);
    struct Queue q;
    InitQueue(&q, 4);
    while(strcmp(input, "END")!=0){

        if(strcmp(input, "ENQ")==0){
            int x;
            scanf("%d", &x);
            Enqueue(&q, x);
        }

        if(strcmp(input, "DEQ")==0){
            printf("%d\n", Dequeue(&q));
        }

        if(strcmp(input, "EMPTY")==0){
            if(QueueEmpty(&q)){
                printf("true\n");
            } else {
                printf("false\n");
            }
        }

        scanf("%s", input);
    }
    free(q.data);
    return 0;
}