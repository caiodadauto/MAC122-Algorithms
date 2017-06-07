#include<stdio.h>
#include<stdlib.h>

int **AlocaMatriz(int m, int n){
    int
        i,
        j,
        **A;

    A = (int **)malloc(m * sizeof(int *));
    for(i = 0; i < m; i++){
        A[i] = (int *)malloc(n * sizeof(int));
    }
    printf("Entre com os valores da matriz da esquerda para direita de cima para baixo:");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            scanf("%d", &A[i][j]);/* *(*(A + i) + j) == *(A[i] + j) == A[i][j]*/
    }
    return A;
}

void FlipVertical(int **A, int m, int n){
    int
        i,
        *aux;

    for(i = 0; i < m/2; i++){
        aux = *(A + i);
        *(A + i) = *(A + m - i - 1);
        *(A + m - i - 1) = aux;
    }
}

int main(){
    int
        j,
        i,
        m,
        n,
        **A;

    printf("Entre com o numero de linhas e colunas:");
    scanf("%d%d", &m, &n);
    A = AlocaMatriz(m, n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            printf("%d\t", A[i][j]);
        printf("\n");
    }
    printf("\n");

    FlipVertical(A, m, n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            printf("%d\t", A[i][j]);
        printf("\n");
    }

    for(i = 0; i < m; i++)
        free(A[i]);
    free(A);
    return 0;
}
