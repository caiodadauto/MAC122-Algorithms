#include <stdio.h>
#include <stdlib.h>

int *IndicesImpares(int A[], int nA, int *nB){
    int
        i,
        j = 0,
        *B;

    for(i = 0; i < nA; i++){
        if(A[i]%2){
            *nB += 1;
        }
    }
    B = (int *)malloc(*nB * sizeof(int));
    for(i = 0; i < nA; i++){
        if(A[i]%2){
            B[j] = i;
            j++;
        }
    }
    return B;
}

int main() {
    char
        aux;
    int
        i,
        nB = 0,
        *B,
        A[100];

    printf("Entre com uma sequencia de numeros: ");
    for(i = 0; aux != '\n'; i++){
        scanf("%c", &aux);
        A[i] = aux - '0';
    }
    B = IndicesImpares(A, i - 1, &nB);
    for(i = 0; i < nB; i++)
        printf("%d", B[i]);
    printf("\n");

    free(B);
    return 0;
}
