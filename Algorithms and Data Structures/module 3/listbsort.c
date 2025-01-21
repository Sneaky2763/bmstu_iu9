#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem {
    struct Elem *next;
    char *word;
};

struct Elem *InitSingleLinkedList() {
    return NULL;
}

struct Elem *InsertAfter(struct Elem *x, struct Elem *y) {
    if (x==NULL) {
        return y;
    }
    struct Elem *curr=x;
    while (curr->next!=NULL) {
        curr=curr->next;
    }
    curr->next=y;
    return x;
}

struct Elem *bsort(struct Elem *list) {
    if (list==NULL) {
        return NULL;
    }
    int swapped=1;
    while(swapped){
        swapped=0;
        struct Elem *curr=list;
        while (curr->next!=NULL) {
            if (strlen(curr->word) > strlen(curr->next->word)) {
                char *swapper=curr->word;
                curr->word=curr->next->word;
                curr->next->word=swapper;
                swapped=1;
            }
            curr=curr->next;
        }
    }
    return list;
}

int main() {
    struct Elem *list=InitSingleLinkedList();

    char string[1001];
    fgets(string, 1001, stdin);

    int len=strlen(string);
    if (len>0 && string[len-1]=='\n') {
        string[len-1]='\0';
    }

    char word[1001];
    int pos=0;

    for (int i=0; i<=len; ++i){
        if (string[i]!=' ' && string[i]!='\0') {
            word[pos]=string[i];
            ++pos;
        } else {
            if(pos>0){
                word[pos]='\0';
                struct Elem *y=malloc(sizeof(struct Elem));
                y->word=malloc(strlen(word) + 1);
                strcpy(y->word, word);
                y->next=NULL;
                list=InsertAfter(list, y);
                pos=0;
            }
        }
    }

    list=bsort(list);

    struct Elem *output=list;
    while (output!=NULL) {
        printf("%s ", output->word);
        struct Elem *curr=output;
        output=output->next;
        free(curr->word);
        free(curr);
    }
    return 0;
}