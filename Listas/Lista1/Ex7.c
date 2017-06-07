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
    return vetor;
}

int main() {
    struct Vetor
        *vetor;
    int
        n;

    printf("Entre com o valor de n: ");
    scanf("%d", &n);
    vetor = AlocaVetor(n);

    free(vetor->Valor);
    free(vetor);
    return 0;
}
