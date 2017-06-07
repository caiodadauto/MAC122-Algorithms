#include <stdio.h>
#include <stdlib.h>

struct Vetor{
    int n;
    int *Valor;
};

struct Vetor *AlocaVetor(int n){
    struct Vetor
        *vetor;

    vetor = (struct Vetor *)malloc(sizeof(struct Vetor));
    vetor->Valor = (int *)malloc(n * sizeof(int));/*Igual a *(vetor).Valor o que é diferente de *vetor.Valor que é igual a *(vetor.Valor)*/
    vetor->n = n;
    return vetor;
}

struct Vetor *IndicesImpares(struct Vetor *A){
    struct Vetor
        *B;
    int
        i,
        nB = 0,
        j = 0;

    for(i = 0; i < A->n; i++){
        if(A->Valor[i]%2)
            nB += 1;
    }
    B = AlocaVetor(nB);
    for(i = 0; i < A->n; i++){
        if(A->Valor[i]%2){
            B->Valor[j] = i;
            j++;
        }
    }
    return B;
}

int main() {
    struct Vetor
        *A,
        *B;
    char
        aux;
    int
        n,
        i,
        AUX[100];

    printf("Entre com uma sequencia de numeros: ");
    for(i = 0; aux != '\n'; i++){
        scanf("%c", &aux);
        AUX[i] = aux - '0';
    }
    n = i - 1;
    A = AlocaVetor(n);
    for(i = 0; i < n; i++)
        A->Valor[i] = AUX[i];

    B = IndicesImpares(A);
    for(i = 0; i < B->n; i++)
        printf("%d", B->Valor[i]);
    printf("\n");

    free(A->Valor);
    free(B->Valor);
    free(A);
    free(B);
    return 0;
}
