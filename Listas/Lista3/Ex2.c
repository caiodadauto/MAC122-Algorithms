#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char TipoDado;
#include "pilhaLig.c"
#define MAX 10000

void Inverte(char A[], char *B){
    Pilha
        p;
    int
        j,
        i;

    p = CriaPilha();
    for(i = 0; A[i] != '\0'; i++)
        Empilha(p, A[i]);
    for(j = 0; !PilhaVazia(p); j++)
        B[j] = Desempilha(p);
    B[j] = '\0';
    LiberaPilha(p);
}

bool FormaWcM(char X[]){
    char
        W[MAX],
        str[MAX];
    int
        i;

    for(i = 0; X[i] != 'c'; i++){
        if(X[i] == '\0')
            return false;
        str[i] = X[i];
    }
    str[i] = '\0';
    Inverte(str, W);
    i++;
    for(; X[i] != '\0'; i++)
        str[i] = X[i];
    str[i] = '\0';
    if(strcmp(str, W))
        return true;
    else
        return false;
}

int main(){
    char
        X[] = "abaabcbaaba";

    if(FormaWcM(X))
        printf("Pretence!\n");
    else
        printf("Nao pertence!\n");
    return 0;
}
