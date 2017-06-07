#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void troca(char *a, char *b){
    char
        temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void permut(char s[], int i, int n){
    int
        j;

    if(i == n)
        printf("%s\n", s);
    for(j = i; j < n; j++){
        troca((s + i), (s + j));
        permut(s, i + 1, n);
        troca((s + i), (s + j));
    }
}

int main(){
    char
        s[150];

    printf("entre com a palavra:");
    scanf("%[^\n]", s);
    permut(s, 0, strlen(s));
    return 0;
}
