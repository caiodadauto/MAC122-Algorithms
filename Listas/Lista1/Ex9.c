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

int *Histograma(int **A, int m, int n){
    int
        i,
        j,
        *H;

    H = (int *)calloc(256, sizeof(int));
    for(i = 0; i < m; i++){
        for (j = 0; j < n; j++)
            ++H[A[i][j]];
    }
    return H;
}

int main(){
    int
        i,
        m,
        n,
        *H;

    printf("Entre com o numero de linhas e colunas:");
    scanf("%d%d", &m, &n);
    H =(int *)Histograma(AlocaMatriz(m, n), m, n);
    for(i = 0; i < 256; i++){
        if(H[i] != 0)
            printf("%d\t->\t%d\n", i, H[i]);
    }

    return 0;
}
