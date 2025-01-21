#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct elem{
    int val;
    int max;
};

struct Stack{
    struct elem *data;
    int cap;
    int top1;
    int top2;
};

void InitDoubleStack(struct Stack *s, int n){
    s->data=malloc(sizeof(struct elem)*n);
    s->cap=n;
    s->top1=0;
    s->top2=n-1;
}

int StackEmpty1(struct Stack *s){
    return (s->top1==0);
}

int StackEmpty2(struct Stack *s){
    return (s->top2==s->cap-1);
}

void Push1(struct Stack *s, struct elem x) {
    if (s->top2<s->top1) {
        return;
    }
    if (s->top1==0) {
        x.max = x.val;
    } else {
        if(x.val>s->data[s->top1 - 1].max){
            x.max=x.val;
        } else {
            x.max=s->data[s->top1 - 1].max;
        }
    }
    s->data[s->top1++]=x;
}

void Push2(struct Stack *s, struct elem x){
    if (s->top2<s->top1) {
        return;
    }
    if (s->top2==s->cap-1) {
        x.max=x.val;
    } else {
        if(x.val>s->data[s->top2+1].max){
            x.max=x.val;
        } else {
            x.max=s->data[s->top2+1].max;
        }
    }
    s->data[s->top2--]=x;
}

struct elem Pop1(struct Stack *s){
    if (StackEmpty1(s)){
        printf("no elements");
    }
    s->top1--;
    return s->data[s->top1];
}

struct elem Pop2(struct Stack *s){
    if (StackEmpty2(s)){
        printf("no elements");
    }
    s->top2++;
    return s->data[s->top2];
}

void InitQueueOnStack(struct Stack *s, int n){
    InitDoubleStack(s, n);
}

int QueueEmpty(struct Stack *s){
    return (StackEmpty1(s) && StackEmpty2(s));
}

void Enqueue(struct Stack *s, struct elem x){
    Push1(s, x);
}

int Dequeue(struct Stack *s){
    if(StackEmpty2(s)){
        while(StackEmpty1(s)==0){
            Push2(s, Pop1(s));
        }
    }
    struct elem x=Pop2(s);
    return x.val;
}

int Max(struct Stack *s){
    if(!(StackEmpty1(s)) && !(StackEmpty2(s))){
        int max1=s->data[s->top1-1].max;
        int max2=s->data[s->top2+1].max;
        if(max1>max2){
            return max1;
        }
        return max2;
    } else if(!StackEmpty1(s)){
        return s->data[s->top1-1].max;
    } else if(!StackEmpty2(s)){
        return s->data[s->top2+1].max;
    }
}

int main(){
    char input[10];
    scanf("%s", input);
    struct Stack q;
    InitQueueOnStack(&q, 1000000);
    while(strcmp(input, "END")!=0){

        if(strcmp(input, "ENQ")==0){
            int x;
            scanf("%d", &x);
            struct elem element;
            element.val=x;
            element.max=x;
            Enqueue(&q, element);
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

        if(strcmp(input, "MAX")==0){
            printf("%d\n", Max(&q));
        }

        scanf("%s", input);
    }
    free(q.data);
    return 0;
}