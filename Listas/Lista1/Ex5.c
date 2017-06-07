#include <stdio.h>
#include <stdlib.h>

int ConsomeEspaco(char texto[], int *i){
    for(; texto[*i] == ' '; *i += 1); /*Devolve valor do primeiro caracter diferente de espaço*/
    if(texto[*i] != '\0')
        return 1;
    else
        return 0;
}

char **VetorDePalavras(char texto[], int *npal){
    int
        k,/*Já inicializado no for*/
        i,/*Já inicializado no for*/
        j = 0,
        inicial = 0;/*Inicio de cada palavra*/
    char
        **aux;

    if(!ConsomeEspaco(texto, &inicial))/*Para consumir os primeiros espaços em brancos, se houver*/
        return NULL;

    i = inicial;
    do{
        *npal += 1;
        for(; texto[i] != ' ' && texto[i] != '\0'; i++);
    }while(ConsomeEspaco(texto, &i));/*Para determinar o número de palavras contido em texto*/
    
    i = inicial;
    aux = (char **)malloc(*npal * sizeof(char *));
    do{
        inicial = i;/*É desnecessario somente no primeiro loop, nos outro atualiza inicial para a proxima palavra*/
        for(; texto[i] != ' ' && texto[i] != '\0'; i++);/*i passa a ser a  posição final da palavra do laço*/
        aux[j] = (char *)malloc((i - inicial + 1) * sizeof(char));/*i - inicial + 1 é o tamanho da palavra mais uma posição para o \0*/
        for(i = inicial, k =  0; texto[i] != ' ' && texto[i] != '\0'; i++, k++)/*Varre novamente a palavra, mas agora escrevendo em um dos vetores k*/
            aux[j][k] = texto[i];
        aux[j][k] = '\0';
        j++;
    }while(ConsomeEspaco(texto, &i));

    return aux;
}

int main() {
    int
        i,
        npal = 0;
    char
        **vetor,
        str[500];

    printf("Entre com uma string: ");
    scanf("%[^\n]", str);
    vetor = VetorDePalavras(str, &npal);
    for(i = 0; i < npal; i++)
        printf("%s\n", vetor[i]);
    
    for(i = 0; i < npal; i++)
        free(vetor[i]);
    free(vetor);
    return 0;
}
