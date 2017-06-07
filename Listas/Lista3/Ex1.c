#include<stdio.h>
#include<stdlib.h>

typedef char TipoDado;
#include "pilhaLig.c"

int main(){
    char
        str[] = "EXERCICIO MUITO COMPLICADO";
    int
        i = 0;
    Pilha
        p;

    p = CriaPilha();
    while(str[i] != '\0'){
        for(; str[i] != ' ' && str[i] != '\0'; i++)
            Empilha(p, str[i]);
        while(!PilhaVazia(p))
            printf("%c", Desempilha(p));
        if(str[i] == ' '){
            printf(" ");
            i++;
        }
        else
            printf("\n");
    }
    LiberaPilha(p);
    return 0;
}
