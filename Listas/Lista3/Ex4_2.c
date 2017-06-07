#include<stdio.h>
#include<stdlib.h>

typedef char TipoDado;
#include "pilhaLig.c"
#define MAX 10000

char ParDeAbertura(char c){
    switch(c){
        case ')': return '(';
        case ']': return '[';
    }
    exit(-1);
}

char ParDeFechamento(char c){
    switch(c){
        case '(': return ')';
        case '[': return ']';
    }
    exit(-1);
}

int BalanceiaCadeia(char *cadeia, char *corr){
    Pilha
        p;
    char
        c;
    int
        i = -1,
        j = -1;
    bool
        continua = true;

    p = CriaPilha();
    while(continua){
        ++i;
        ++j;
        switch(cadeia[i]){
            case '\0':
                continua = false;
                while(!PilhaVazia(p)){
                    c = Desempilha(p);
                    corr[j] = ParDeFechamento(c);
                    ++j;
                }
            break;

            case '(':
            case '[':
                Empilha(p, cadeia[i]);
                corr[j] = cadeia[i];
            break;

            case ')':
            case ']':
                if(PilhaVazia(p)){
                    corr[j] = ParDeAbertura(cadeia[i]);
                    j++;
                    corr[j] = cadeia[i];
                }
                else{
                    c = Desempilha(p);
                    if(c != ParDeAbertura(cadeia[i])){
                        corr[j] = ParDeAbertura(cadeia[i]);
                        j++;
                        corr[j] = cadeia[i];
                        Empilha(p, c);
                    }
                    else
                        corr[j] = cadeia[i];
                }
            break;
        }
    }
    corr[j] = '\0';
    LiberaPilha(p);
    return j - i;
}

int main(){
    int
        n;
    char
        corr[MAX],
        cadeia[] = "(((()()())(()(((()()())(()(((()()())(()(((()()())(()(((()()())(()(((()()())(()(((()()())]]";

    n = BalanceiaCadeia(cadeia, corr);
    printf("%s\t%d\n", corr, n);
    return 0;
}
