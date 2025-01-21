#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    if (argc!=4){
        printf("Usage: frame <height> <width> <text>");
        return 0;
    }
    int height=atoi(argv[1]);
    int width=atoi(argv[2]);
    int textlen=strlen(argv[3]);
    
    if (height<3 || width<textlen+2){
        printf("Error");
        return 0;
    } else {
        for (int i=0; i<height; ++i){
            for(int j=0; j<width; ++j){
                if (i==0 || i==height-1){
                    printf("*");
                } else {
                    if (j==0 || j==width-1){
                        printf("*");
                    } else {
                        if(i==(height+1)/2-1 && j==(width-textlen)/2){
                            printf(argv[3]);
                            j+=textlen-1;
                        } else {
                            printf(" ");
                        }
                    }
                }
            }
            printf("\n");
        }
    }
    return 0;
}