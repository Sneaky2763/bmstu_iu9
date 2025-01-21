#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void csort(char *src, char *dest){
    char **words=(char **)malloc(2000*sizeof(char *));
    int i=0;
    char srccopy[2000]={0};
    for(int i=0; src[i]!='\0'; ++i){
        srccopy[i]=src[i];
    }
    char *curr_word=strtok(srccopy, " ");
    while(curr_word != NULL){
        words[i]=curr_word;
        curr_word=strtok(NULL, " ");
        ++i;
    }
    if(words[i-1][strlen(words[i-1])-1]=='\n'){
        words[i-1][strlen(words[i-1])-1]='\0';
    }
    int n=i;
    
    int j=0;
    int count[n];
    for(int i=0; i<n; ++i){
        count[i]=0;
    }
    while(j<n-1){
        i=j+1;
        while(i<n){
            if(strlen(words[i])<strlen(words[j])){
                ++count[j];
            } else{
                ++count[i];
            }
            ++i;
        }
        ++j;
    }

    int pos=0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(count[j]==i){
                for(int k=0; words[j][k]!='\0'; ++k){
                    dest[pos]=words[j][k];
                    ++pos;
                }
                dest[pos]=' ';
                ++pos;
            }
        }
    }
    dest[--pos]='\0';
    free(words);
    return;
}

int main(){
    char src[2000];
    char dest[2000]={0};
    fgets(src, 2000, stdin);
    csort(src, dest);
    printf("%s", dest);
}