#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem {
    struct Elem *prev, *next;
    int v;
};

struct Elem *InitDoubleLinkedList(){
    struct Elem *l=malloc(sizeof(struct Elem));
    l->prev=l;
    l->next=l;
    return l;
}

void InsertAfter(struct Elem *x, struct Elem *y){
    struct Elem *z;
    z=x->next;
    x->next=y;
    y->prev=x;
    y->next=z;
    z->prev=y;
}

void Delete(struct Elem *x){
    struct Elem *y=x->prev;
    struct Elem *z=x->next;
    y->next=z;
    z->prev=y;
    x->prev=NULL;
    x->next=NULL;
}

void InsertionSort(struct Elem *l){
    struct Elem *curr;
    struct Elem *behind;
    curr=l->next;
    while(curr!=l){
        behind=curr->prev;
        while(behind!=l && behind->v > curr->v){
            behind=behind->prev;
        }
        Delete(curr);
        InsertAfter(behind, curr);
        curr=curr->next;
    }
}

int main(){
    struct Elem *l=InitDoubleLinkedList();
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; ++i){
        struct Elem *a=malloc(sizeof(struct Elem));
        scanf("%d", &a->v);
        InsertAfter(l, a);
    }

    InsertionSort(l);

    struct Elem *output=l->next;
    while(output!=l){
        printf("%d ", output->v);
        struct Elem *curr=output;
        output=output->next;
        free(curr);
    }

    free(l);
    return 0;
}