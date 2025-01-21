#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

char stroka[1000001];

int main(){
    int letter_count[26]={0};
    scanf("%s", stroka);
    
    for (int i=0; i<1000001; ++i){
        if(stroka[i]=='\0'){
            break;
        } else {
            letter_count[stroka[i]-'a']++;
        }
    }

    for(int i=0; i<26; ++i){
        while(letter_count[i]!=0){
            printf("%c", i+'a');
            letter_count[i]--;
        }
    }
    return 0;
}