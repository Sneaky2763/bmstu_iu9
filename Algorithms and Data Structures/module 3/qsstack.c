#include <stdio.h>
#include <stdlib.h>

struct Task {
    int low, high;
};

struct stack{
    struct Task task;
    struct stack *prev;
};


struct stack* Push(struct stack *prev, int low, int high){
    struct stack *new=malloc(sizeof(struct stack));
    new->prev=prev;
    new->task.low=low;
    new->task.high=high;
    return new;
}

struct stack* Pop(struct stack *s, struct Task *task){
    *task=s->task;
    struct stack *next=s->prev;
    free(s);
    return next;
}

int partition(int low, int high, int *num) {
    int i=low-1;
    for(int j=low; j<high; ++j){
        if(num[j]<num[high]){
            ++i;
            int swapper=num[j];
            num[j]=num[i];
            num[i]=swapper;
        }
    }
    int swapper=num[i+1];
    num[i+1]=num[high];
    num[high]=swapper;
    return i+1;
}

void quicksort(int n, int *num) {
    struct stack *s=NULL;

    s=Push(s, 0, n-1);

    while(s!=NULL){
        struct Task task;
        s=Pop(s, &task);

        int low=task.low;
        int high=task.high;
        if(low<high) {
            int q=partition(low, high, num);
            if(q-1>low){
                s=Push(s, low, q-1);
            } 
            if(q+1<high){
                s=Push(s, q+1, high);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int num[n];
    for (int i=0; i<n; ++i){
        scanf("%d", &num[i]);
    }

    quicksort(n, num);

    for (int i=0; i<n; ++i){
        printf("%d ", num[i]);
    }
    
    return 0;
}