#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack{
    int *data;
    int cap;
    int top;
};

void InitStack(struct Stack *s, int n){
    s->data=(int *)malloc(sizeof(int)*n);
    s->cap=n;
    s->top=0;
}

int StackEmpty(struct Stack *s){
    return (s->top==0);
}

void Push(struct Stack *s, int x){
    if (s->top==s->cap){
        return;
    }
    s->data[s->top]=x;
    s->top++;
}

int Pop(struct Stack *s){
    if (StackEmpty(s)){
        return 0;
    }
    s->top--;
    int x=s->data[s->top];
    return x;
}

int main(){
    char input[10];
    scanf("%s", input);
    struct Stack s;
    InitStack(&s, 1000000);
    while(strcmp(input, "END")!=0){

        if(strcmp(input, "CONST")==0){
            int x;
            scanf("%d", &x);
            Push(&s, x);
        }

        if(strcmp(input, "ADD")==0){
            int a=Pop(&s);
            int b=Pop(&s);
            Push(&s, a+b);
        }

        if(strcmp(input, "SUB")==0){
            int a=Pop(&s);
            int b=Pop(&s);
            Push(&s, a-b);
        }

        if(strcmp(input, "MUL")==0){
            int a=Pop(&s);
            int b=Pop(&s);
            Push(&s, a*b);
        }

        if(strcmp(input, "DIV")==0){
            int a=Pop(&s);
            int b=Pop(&s);
            Push(&s, a/b);
        }

        if(strcmp(input, "MAX")==0){
            int a=Pop(&s);
            int b=Pop(&s);
            if(a>b){
                Push(&s, a);
            } else {
                Push(&s, b);
            }
        }

        if(strcmp(input, "MIN")==0){
            int a=Pop(&s);
            int b=Pop(&s);
            if(a<b){
                Push(&s, a);
            } else {
                Push(&s, b);
            }
        }

        if(strcmp(input, "NEG")==0){
            int a=Pop(&s);
            Push(&s, -a);
        }

        if(strcmp(input, "DUP")==0){
            int a=Pop(&s);
            Push(&s, a);
            Push(&s, a);
        }

        if(strcmp(input, "SWAP")==0){
            int a=Pop(&s);
            int b=Pop(&s);
            Push(&s, a);
            Push(&s, b);
        }

        scanf("%s", input);
    }
    
    printf("%d", s.data[s.top-1]);
    free(s.data);
    return 0;
}