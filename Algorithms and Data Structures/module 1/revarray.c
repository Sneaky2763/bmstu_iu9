#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void revarray(void *base, size_t nel, size_t width){
    char *element = (char *) base;
    char swapper;

    for (int i=0; i<nel/2; ++i) {
            for (int j=0; j<width; ++j){
                memcpy(&swapper, element+i*width+j, 1);
                memcpy(element+i*width+j, element+(nel-i-1)*width+j, 1);
                memcpy(element+(nel-i-1)*width+j, &swapper, 1);
            } 
        }
}