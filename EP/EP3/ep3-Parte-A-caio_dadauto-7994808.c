/* EP03-Parte A - Turma 01 Paulo Miranda
 * 
 * AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
 * TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
 * DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
 * E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
 * POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
 * SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
 * REPROVAÇÃO DIRETA NA DISCIPLINA.
 *
 * Nome: Caio Dadauto
 * NUSP: 7994808
 *
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*---Definicao de estrutura e typedef---*/
struct Vertice{
    float
        x,
        y;
    struct Vertice
        *prox;
};
typedef struct Vertice * Poligono;
/*--------------------------------------*/

/*-------Cabeçalho de Funcoes-----------*/
int NumeroDeVertices(Poligono P);                                               /*Retorna o numero de vertices de um poligono*/
int **AlocaMatrizInicializada(int m, int n);                                    /*Aloca Matriz mxn inicializada com 255*/
Poligono AlocaVertice();                                                        /*Aloca dinamicamente um struct Vertice retornando o mesmo*/
Poligono PoligonoPorPontoMedio(Poligono P);                                     /*Gera poligono a partir dos pontos medios de outro P*/
void LiberaPoligono(Poligono P);                                                /*Libera Poligono P*/
void LiberaMatriz(int **M, int m);                                              /*Libera Matriz M*/
void AdicionaVertice(Poligono *P, float x, float y);                            /*Adicona vertice ao poligono P*/
void DesenhaSequenciaDePoligono(Poligono P, int val, int R);                    /*Desenha R poligonos na matriz M*/ 
void DrawLine(int **M, int m, int n, int x1, int y1, int x2, int y2, int val);  /*Desenha segmento de reta entre os pontos (x1,x2) e (y1,y2)*/
/*--------------------------------------*/

/*--Manipulacao de poligonos e matrizes-*/
Poligono AlocaVertice(){
    struct Vertice
        *vertice;

    vertice = (struct Vertice *)malloc(sizeof(struct Vertice));
    if(vertice == NULL){
        printf("Falta de Memória!\n");
        exit(-1);
    }
    return vertice;
}

int **AlocaMatrizInicializada(int m, int n){
    int
        **M,
        j,
        i;

    M = (int **)malloc(m * sizeof(int *));
    for(i = 0; i < m; i++)
        M[i] = (int *)malloc(n * sizeof(int));
    for(i = 0; i < 480; i++){
        for(j = 0; j < 640; j++)
            M[i][j] = 255;
    }
    return M;
}

void AdicionaVertice(Poligono *P, float x, float y){
/*Os poligonos sao listas circulares sem no cabeca
 *com ponteiro P apontando para o ultimo elemento adiconado*/
    Poligono
        Q;

    Q = AlocaVertice();
    Q->x = x;
    Q->y = y;
    if(*P == NULL)
        Q->prox = Q;
    else{
        Q->prox = (*P)->prox;
        (*P)->prox = Q;
    }
    *P = Q;
}

void LiberaPoligono(Poligono P){
    Poligono
        T,
        Q = P->prox;

    do{
        T = Q;
        Q = Q->prox;
        free(T);
    }while(Q != P);
    free(P);
}

void LiberaMatriz(int **M, int m){
    int
        i;

    for(i = 0; i < m; i++)
        free(M[i]);
    free(M);
}
/*--------------------------------------*/

/*--------Funcoes Obrigatorias----------*/
int NumeroDeVertices(Poligono P){
    Poligono
        Q;
    int
        num = 0;

    Q = P;
    do{
        ++num;
        Q = Q->prox;
    }while(Q->prox != P);
    return num;
}

Poligono PoligonoPorPontoMedio(Poligono P){
    float
        xMedio,
        yMedio;
    Poligono
        T,
        Q = NULL;

    if (NumeroDeVertices(P) < 3)
        exit(1);

    T = P;
    do{
        xMedio = (T->x + T->prox->x)/2;
        yMedio = (T->y + T->prox->y)/2;
        AdicionaVertice(&Q, xMedio, yMedio);
        T = T->prox;
    }while(T != P);
    return Q;
}

void DrawLine(int **M, int m, int n, int x1, int y1, int x2, int y2, int val){
    float 
        x,
        y,
        dx,
        dy;
    int
        xi,
        yi;

    dx = (x2-x1);
    dy = (y2-y1);
    if(fabs(dx) > fabs(dy)){
        dy = dy/(fabs(dx));
        dx = dx/(fabs(dx));
    }
    else{
        dx = dx/(fabs(dy));
        dy = dy/(fabs(dy));
    }
    x = (float)x1;
    y = (float)y1;
    xi = x1;
    yi = y1;
    while(xi != x2 || yi != y2){
        if(yi >= 0 && yi < m && xi >= 0 && xi < n)
            M[yi][xi] = val;
        x += dx;
        y += dy;
        xi = (int)(x + 0.5);
        yi = (int)(y + 0.5);
    }
    if(y2 >= 0 && y2 < m && x2 >= 0 && x2 < n)
        M[y2][x2] = val;
}
/*--------------------------------------*/

/*----------Funcoes Auxiliares----------*/
void DesenhaSequenciaDePoligono(Poligono P, int val, int R){
    Poligono
        Q;
    FILE
        *arquivo;
    int
        **M,
        i,
        j;

    M = AlocaMatrizInicializada(480, 640);
    arquivo = fopen("poligono.pgm", "w");
    fprintf(arquivo, "P2\n640\t480\n255\n");
    for(i = 0; i < R; i++){
        Q = P;
        do{
            DrawLine(M, 480, 640, (int)Q->x, (int)Q->y, (int)Q->prox->x, (int)Q->prox->y, val);
            Q = Q->prox;
        }while(Q != P);
        P = PoligonoPorPontoMedio(P);
        LiberaPoligono(Q);
    }
    for(i = 0; i < 480; i++){
        for(j = 0; j < 640; j++)
            fprintf(arquivo, "%d\t", M[i][j]);
        fprintf(arquivo, "\n");
    }
    LiberaMatriz(M, 480);
    fclose(arquivo);
}
/*--------------------------------------*/

int main(){
    FILE
        *entrada;
    char
        str[100];
    float
        x,
        y;
    Poligono
        P = NULL;
    int
        R;

    printf("Entre com o nome do arquivo com as coordenadas do Poligono:");
    scanf("%[^\n]", str);
    entrada = fopen(str, "r");
    if(entrada == NULL)
        exit(1);
    while(!feof(entrada)){
        fscanf(entrada, " %f%f ", &x, &y);
        AdicionaVertice(&P, x, y);
    }

    printf("Entre com o numero de sequencias de poligonos desejadas:");
    scanf(" %d", &R);
    DesenhaSequenciaDePoligono(P, 0, R);
    fclose(entrada);
    return 0;
}
