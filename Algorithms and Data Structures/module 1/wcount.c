#include <stdio.h>

int wcount(char *s){
    int curr_char=0;
    int word_count=1;
    
    if(s[curr_char]=='\0'){
        return 0;
    }
    
    while(s[curr_char]!='\0'){
        if (s[curr_char]!=' ' && s[curr_char+1]==' '){
            word_count++;
        }
        ++curr_char;
    }
    if (s[curr_char-1]==' '){
        word_count--;
    }

    return word_count;
}

int main(){
    char stroka[2000];
    gets(stroka);
    printf("%d", wcount(stroka));
    return 0;
}