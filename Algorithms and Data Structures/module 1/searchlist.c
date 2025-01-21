#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "elem.h"

struct Elem  *searchlist(struct Elem  *list, int k){
    if (list==NULL){
        return NULL;
    }
    if((list->tag==INTEGER)&&(list->value.i==k)){
        return list;
    }
    if (list->tail==NULL){
        return NULL;
    }

    searchlist(list->tail, k);
}