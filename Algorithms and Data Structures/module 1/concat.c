#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat(char **s, int n){
    int size=1;
    for(int i=0; i<n; ++i){
        size+=strlen(s[i]);
    }
    char *res;
    res=(char*)malloc(size * sizeof(char));
    int curr_word=0;
    int i=0;
    while(i<size-1){
        for(int j=0; j<1000000 && s[curr_word][j]!='\0'; ++j){
            res[i]=s[curr_word][j];
            ++i;
        }
        ++curr_word;
    }
    res[size-1]='\0';
    return res;
}

int main(){
    int n;
    scanf("%d", &n);

    char **strings;
    strings=(char**)malloc(n * sizeof(char*));
    for (int i=0; i<n; i++) {
        strings[i] = (char*)malloc(1001 * sizeof(char));
        scanf("%s", strings[i]);
    }

    char *result = concat(strings, n);
    printf("%s", result);
    free(result);

    for(int i=0; i<n; ++i){
        free(strings[i]);
    }
    free(strings);
    return 0;
}