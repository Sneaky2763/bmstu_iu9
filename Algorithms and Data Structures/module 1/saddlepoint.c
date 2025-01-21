#include <stdio.h>

int max(int a, int b){
    if (a>b){
        return a;
    }
    return b;
}

int min(int a, int b){
    if (a<b){
        return a;
    }
    return b;
}

int main(){
    int height, width;
    scanf("%d %d", &height, &width);
    
    int matrix[height][width];
    for (int i=0; i<height; ++i){
        for (int j=0; j<width; ++j){
            scanf("%d", &matrix[i][j]);
        }
    }
    
    int max_str[10]={1<<31, 1<<31, 1<<31, 1<<31, 1<<31, 1<<31, 1<<31, 1<<31, 1<<31, 1<<31};
    int min_stolb[10]={1<<30, 1<<30, 1<<30, 1<<30, 1<<30, 1<<30, 1<<30, 1<<30, 1<<30, 1<<30};

    for (int i=0; i<height; ++i){
        for (int j=0; j<width; ++j){
            max_str[i]=max(max_str[i], matrix[i][j]);
            min_stolb[j]=min(min_stolb[j], matrix[i][j]);
        }
    }
    
    for (int i=0; i<height; ++i){
        for (int j=0; j<width; ++j){
            if (max_str[i]==min_stolb[j]){
                printf("%d %d", i, j);
                return 0;
            }
        }
    }

    printf("none");
    return 0;
}