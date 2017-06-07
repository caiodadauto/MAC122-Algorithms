#include<stdio.h>
#include<stdlib.h>

typedef int TipoDado;
#include "pilhaLig.c"


int ValorPos(char pos[]){
    Pilha
        p;
    int
        x,
        y,
        aux,
        i = 0;

    p = CriaPilha();
    while(pos[i] != '\0'){
        for(; pos[i] != '*' && pos[i] != '+' && pos[i] != '\0'; i++)
            Empilha(p, (int)(pos[i] - '0'));
        if(pos != '\0'){
            x = Desempilha(p);
            y = Desempilha(p);
            if(pos[i] == '*')
                aux = y * x;
            else
                aux = y + x;
            Empilha(p, aux);
            ++i;
        }
    }
    LiberaPilha(p);
    return aux;
}

int main(){
    int
        valor;
    char
        pos[] = "123+*45+*6*";

    valor = ValorPos(pos);
    printf("Valor -> %d\n", valor);
    return 0;
}
