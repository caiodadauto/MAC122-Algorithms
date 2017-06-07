/* EP03-Parte B - Turma 01 Paulo Miranda
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
#include<float.h>
#include<math.h>
#define PI 3.14159264

/*---Definicao de estrutura e typedef---*/
typedef struct _Ponto{
    double    
        x,
        y;
} Ponto;
/*--------------------------------------*/

/*-------Cabeçalho de Funcoes-----------*/
int **AlocaMatrizInicializada(int m, int n);                                    /*Aloca Matriz mxn inicializada com 255*/
int **GeraCurvaDeLevy(int R, double dist);                                      /*Gera curva para um segmento com extremidades dist do centro*/
int **GeraEstrelaDeKoch(int R, double dist);                                    /*Gera estrela para um triangulo de vertices dist do centro*/
void LiberaMatriz(int **M, int m);                                              /*Libera Matriz M*/
void GravaFractal(int **M, int m, int n, char str[]);                           /*Grava M em uma imagem de nome str liberando M no final*/
void RotacaoDeUmVetor(Ponto p1, Ponto p2, Ponto *p, float ang);                 /*Rotaciona um vetor (p1-p2) em um angulo igual a "ang"*/
void CurvaDeLevy(int **M, int m, int n, int R, Ponto p1, Ponto p2);             /*Funcao recursiva para desenhar a curva C*/
void EstrelaDeKoch(int **M, int m, int n, int R, Ponto p1, Ponto p2);           /*Funcao recursiva para desenhar a estrela de Koch*/
void DrawLine(int **M, int m, int n, int x1, int y1, int x2, int y2, int val);  /*Desenha segmento de reta entre os pontos (x1,x2) e (y1,y2)*/
void DivideRetaTresPartes(Ponto p1, Ponto p2, Ponto *pNovo1, Ponto *pNovo2);    /*Secciona reta em 3 partes iguais*/
/*--------------------------------------*/

/*--Manipulacao de poligonos e matrizes-*/
int **AlocaMatrizInicializada(int m, int n){
    int
        **M,
        j,
        i;

    M = (int **)malloc(m * sizeof(int *));
    for(i = 0; i < m; i++)
        M[i] = (int *)malloc(n * sizeof(int));
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            M[i][j] = 255;
    }
    return M;
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
void RotacaoDeUmVetor(Ponto p1, Ponto p2, Ponto *p, float ang){
    float
        ROT[2][2],/*Matriz de rotacao*/
        vetorNovo[] = {0, 0},
        vetorVelho[2];
    int
        i,
        j;

    ROT[0][0] = cos(ang);   ROT[0][1] = sin(ang);
    ROT[1][0] = -sin(ang);   ROT[1][1] = cos(ang);
    vetorVelho[0] = p2.x - p1.x;/*Os vetores sao criados de forma a estarem no 1 ou 4 quadrante*/
    vetorVelho[1] = p2.y - p1.y;    
    for(i = 0; i < 2; i++){
        for(j = 0; j < 2; j++)
            vetorNovo[i] += ROT[i][j] * vetorVelho[j];
    }
    p->x = vetorNovo[0] + p1.x;
    p->y = vetorNovo[1] + p1.y;
}

void DivideRetaTresPartes(Ponto p1, Ponto p2, Ponto *pNovo1, Ponto *pNovo2){
    pNovo1->x = (p2.x + 2.0 * p1.x)/3.0;
    pNovo1->y = (p2.y + 2.0 * p1.y)/3.0;
    pNovo2->x = (2.0 * p2.x + p1.x)/3.0;
    pNovo2->y = (2.0 * p2.y + p1.y)/3.0;
}

int **GeraEstrelaDeKoch(int R, double dist){
    int
        i,
        **M;
    Ponto
        pontoMedio,
        pontoTrian[4];

    M = AlocaMatrizInicializada(601, 601);
    pontoTrian[1].x = 300;
    pontoTrian[1].y = 300 - dist;
    pontoMedio.x = 300;
    pontoMedio.y = pontoTrian[1].y + sqrt(3) * dist;
    RotacaoDeUmVetor(pontoTrian[1], pontoMedio, &pontoTrian[2], PI/6.0);
    RotacaoDeUmVetor(pontoTrian[1], pontoMedio, &pontoTrian[0], -PI/6.0);
    pontoTrian[3].x = pontoTrian[0].x;
    pontoTrian[3].y = pontoTrian[0].y;
    for(i = 0; i < 3; i++){
        EstrelaDeKoch(M, 601, 601, R, pontoTrian[i], pontoTrian[i + 1]);
        if(R == 0)
            DrawLine(M, 601, 601, (int)pontoTrian[i].x, (int)pontoTrian[i].y, (int)pontoTrian[i + 1].x, (int)pontoTrian[i + 1].y, 0);
    }
    return M;
}

void EstrelaDeKoch(int **M, int m, int n, int R, Ponto p1, Ponto p2){
    Ponto
        p1Novo,
        p2Novo,
        p3Novo;/*Os pontos sao ordenados em ordem crescente de x*/

    if(R == 0)
        return;
    DivideRetaTresPartes(p1, p2, &p1Novo, &p3Novo);
    RotacaoDeUmVetor(p1Novo, p3Novo, &p2Novo, PI/3.0);
    R--;
    EstrelaDeKoch(M, m, n, R, p1, p1Novo);
    EstrelaDeKoch(M, m, n, R, p1Novo, p2Novo);
    EstrelaDeKoch(M, m, n, R, p2Novo, p3Novo);
    EstrelaDeKoch(M, m, n, R, p3Novo, p2);
    if(R == 0){
        DrawLine(M, m, n, (int)p1.x, (int)p1.y, (int)p1Novo.x, (int)p1Novo.y, 0);
        DrawLine(M, m, n, (int)p1Novo.x, (int)p1Novo.y, (int)p2Novo.x, (int)p2Novo.y, 0);
        DrawLine(M, m, n, (int)p2Novo.x, (int)p2Novo.y, (int)p3Novo.x, (int)p3Novo.y, 0);
        DrawLine(M, m, n, (int)p3Novo.x, (int)p3Novo.y, (int)p2.x, (int)p2.y, 0);
    }
}

int **GeraCurvaDeLevy(int R, double dist){
    int
        **M;
    Ponto
        p1Reta,
        p2Reta;

    M = AlocaMatrizInicializada(601, 601);
    p1Reta.x = 300 - dist;
    p1Reta.y = 300;
    p2Reta.x = 300 + dist;
    p2Reta.y = 300;
    CurvaDeLevy(M, 601, 601, R, p1Reta, p2Reta);
    if(R == 0)
        DrawLine(M, 601, 601, (int)p1Reta.x, (int)p1Reta.y, (int)p2Reta.x, (int)p2Reta.y, 0);
    return M;
}

void CurvaDeLevy(int **M, int m, int n, int R, Ponto p1, Ponto p2){
    Ponto
        pNovo;

    if(R == 0)
        return;
    pNovo.x = (p2.x - p1.x)/sqrt(2) + p1.x;
    pNovo.y = (p2.y - p1.y)/sqrt(2) + p1.y;
    RotacaoDeUmVetor(p1, pNovo, &pNovo, -PI/4.0);
    R--;
    CurvaDeLevy(M, m, n, R, p1, pNovo);
    CurvaDeLevy(M, m, n, R, pNovo, p2);
    if(R == 0){
        DrawLine(M, m, n, (int)p1.x, (int)p1.y, (int)pNovo.x, (int)pNovo.y, 0);
        DrawLine(M, m, n,(int)pNovo.x, (int)pNovo.y, (int)p2.x, (int)p2.y, 0);
    }
}

void GravaFractal(int **M, int m, int n, char str[]){
    FILE
        *arquivo;
    int
        i,
        j;

    arquivo = fopen(str, "w");
    fprintf(arquivo, "P2\n601\t601\n255\n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            fprintf(arquivo, "%d\t", M[i][j]);
        fprintf(arquivo, "\n");
    }
    LiberaMatriz(M, m);
    fclose(arquivo);
}
/*--------------------------------------*/

int main(){
    int
        Rkoch,
        Rlevy;
    double
        distLevy = -1,
        distKoch = -1;

    printf("--------------------------------------------Estrela de Koch-----------------------------------------------------\n");
    printf("\tEntre com o numero de iteracoes desejadas para a estrela de koch:");
    scanf(" %d", &Rkoch);
    printf("\n");
    while(distKoch <= 0 || distKoch > 260){
        printf("\tEntre com a distancia entre o centro da imagem e os vertices do triangulo que da inicio a estrela de koch \
        \n\t(a distancia deve ser maior que zero e menor que 260):");
        scanf(" %lf", &distKoch);
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("---------------------------------------------Curva De Levy------------------------------------------------------\n");
    printf("\tEntre com o numero de iteracoes desejadas para a curva de Levy:");
    scanf(" %d", &Rlevy);
    printf("\n");
    while(distLevy <= 0 || distLevy > 130){
        printf("\tEntre com a distancia entre o centro da imagem e as extremidades da reta que da inicio a curva de Levy \
        \n\t(a distancia deve ser maior que zero e menor que 130):");
        scanf(" %lf", &distLevy);
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
    GravaFractal(GeraEstrelaDeKoch(Rkoch, distKoch), 601, 601, "estrela.pgm");
    GravaFractal(GeraCurvaDeLevy(Rlevy, distLevy), 601, 601, "curvalevy.pgm");
    return 0;
}
