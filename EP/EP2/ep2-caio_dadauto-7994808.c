/* EP02 - Turma 01 Paulo Miranda
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
#include<string.h>
#include<math.h>

struct ImagemRGB{
    int
        **R,
        **G,
        **B,
        m,
        n;
};

struct Descritor{
    char
        filename[512];
    float
        *hist;
    struct Descritor
        *prox;
};

typedef struct Descritor * ListaDescritores;

struct Ranking{
    char
        filename[512];
    float
        dist;
    struct Ranking
        *prox;
};

typedef struct Ranking * ListaRanking;

int **AlocaMatriz(int m, int n);
void LiberaImagemRGB(struct ImagemRGB *I);
void LiberaMatriz(int **M, int m);
void ImprimeRanking(ListaRanking R);
void RemoveListaR(struct Ranking **R);
void LiberaRanking(struct Ranking **R);
void RemoveListaD(struct Descritor **D);
void LiberaDescritores(struct Descritor **D);
void InsereNaListaDescritor(struct Descritor **l, char filename[], float *hist);
float *HistogramaCores(struct ImagemRGB *I);
float DistanciaHistogramas(float *hist1, float *hist2);
float *BuscaHistograma(char filename[], ListaDescritores ListaD);
struct ImagemRGB *AlocaImagemRGB(int m, int n);
struct ImagemRGB *AbreImagemRGB(char filename[]);
ListaDescritores CriaListaDescritores(char arquivo[]);
ListaRanking InsereNoRanking(ListaRanking R, float d, char filename[]);
ListaRanking ComparaDistancias(char filename[], ListaDescritores ListaD);
/*-----------------------------------------------------------------------------------*/
/*----------------------------Funcoes Obrigatorias-----------------------------------*/
int **AlocaMatriz(int m, int n){
    int
        i,
        **A;

    A = (int **)malloc(m * sizeof(int *));
    for(i = 0; i < m; i++)
        A[i] = (int *)malloc(n * sizeof(int));
    return A;
    
}

void LiberaMatriz(int **M, int m){
    int
        i;

    for(i = 0; i < m; i++)
        free(M[i]);
    free(M);
}

void LiberaImagemRGB(struct ImagemRGB *I){
    LiberaMatriz(I->R, I->m);
    LiberaMatriz(I->G, I->m);
    LiberaMatriz(I->B, I->m);
    free(I);
}

struct ImagemRGB *AlocaImagemRGB(int m, int n){
    struct ImagemRGB
        *imgRGB;

    imgRGB = (struct ImagemRGB *)malloc(sizeof(struct ImagemRGB));
    imgRGB->m = m;
    imgRGB->n = n;
    imgRGB->R = AlocaMatriz(m, n);
    imgRGB->G = AlocaMatriz(m, n);
    imgRGB->B = AlocaMatriz(m, n);
    return imgRGB;
}

struct ImagemRGB *AbreImagemRGB(char filename[]){
    struct ImagemRGB
        *imgRGB;
    FILE
        *entrada;
    int
        i,
        j,
        m,
        n;

    entrada = fopen(filename, "r");
    if(entrada == NULL){
        printf("Imagem %s nao encontrada!\n", filename);
        exit(1);
    }
    fseek(entrada, 3, SEEK_SET);
    fscanf(entrada, "%d %d", &n, &m);
    fseek(entrada, sizeof(int), SEEK_CUR);
    imgRGB = AlocaImagemRGB(m, n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            fscanf(entrada, "%d", &imgRGB->R[i][j]);
            fscanf(entrada, "%d", &imgRGB->G[i][j]);
            fscanf(entrada, "%d", &imgRGB->B[i][j]);
        }
    }
    fclose(entrada);
    return imgRGB;
}

float *HistogramaCores(struct ImagemRGB *I){
    float
        *hist;
    int
        i,
        j;

    hist = (float *)calloc(64, sizeof(float));
    for(i = 0; i < I->m; i++){
        for(j = 0; j < I->n; j++){
            ++hist[(I->R[i][j]/64) + 4 * (I->G[i][j]/64) + 16 * (I->B[i][j]/64)];
        }
    }
    for(i = 0; i < 64; i++)
        hist[i] /= I->m * I->n;

    LiberaImagemRGB(I);
    return hist;
}

float DistanciaHistogramas(float *hist1, float *hist2){
    int
        i;
    float
        soma = 0.0;

    for(i = 0; i < 64; i++)
        soma += pow(hist1[i] - hist2[i], 2);

    return sqrt(soma); 
}

ListaRanking InsereNoRanking(ListaRanking R, float d, char filename[]){
    ListaRanking
        t,
        q;
    
    t = R;
    q = (ListaRanking)malloc(sizeof(struct Ranking));
    strcpy(q->filename, filename);
    q->dist = d;
    if(t == NULL || R->dist > q->dist){
        q->prox = t;
        t = q;
        return t;
    }
    while(t->prox != NULL && q->dist > t->prox->dist)
        t = t->prox;
    q->prox = t->prox;
    t->prox = q;
    return R;
}

void LiberaRanking(struct Ranking **R){
    ListaRanking
        aux;

    while(*R != NULL){
        aux = *R;
        *R = aux->prox;
        free(aux);
    }
}

void LiberaDescritores(struct Descritor **D){
    ListaDescritores
        aux;

    while(*D != NULL){
        aux = *D;
        *D = aux->prox;
        free(aux->hist);
        free(aux);
    }
}

/*-----------------------------------------------------------------------------------*/
/*-----------------------------Funcoes Auxiliares------------------------------------*/
void InsereNaListaDescritor(struct Descritor **l, char filename[], float *hist){
    ListaDescritores
        aux;

    aux = (ListaDescritores)malloc(sizeof(struct Descritor));
    strcpy(aux->filename, filename);
    aux->hist = hist;
    aux->prox = *l;
    *l = aux;
}

float *BuscaHistograma(char filename[], ListaDescritores ListaD){
    ListaDescritores
        aux;

    aux = ListaD;
    while(aux->prox != NULL && strcmp(aux->filename, filename) != 0)
        aux = aux->prox;
    if(strcmp(aux->filename, filename) != 0)
        return NULL;
    else
        return aux->hist;
}

void ImprimeRanking(ListaRanking R){
    printf("\nFiguras mais\tDistancia em relacao\nsimilares\tfigura de busca\n");
    while(R != NULL){
        printf("%s\t%f\n", R->filename, R->dist);
        R = R->prox;
    }
}

ListaDescritores CriaListaDescritores(char arquivo[]){
    FILE
        *entrada;
    ListaDescritores
        ListaD = NULL;
    float
        *hist;
    char
        filename[512];

    entrada = fopen(arquivo, "r");
    if(entrada == NULL){
        printf("Arquivo nao encontrado!\n");
        exit(1);
    }
    printf("Carregando...\n");
    while(!feof(entrada)){
        fscanf(entrada, " %s ", filename);
        hist = HistogramaCores(AbreImagemRGB(filename));
        InsereNaListaDescritor(&ListaD, filename, hist);
    }
    printf("As imagens especificadas no arquivo %s foram carregadas com sucesso!\n", arquivo);
    fclose(entrada);
    return ListaD;
}

ListaRanking ComparaDistancias(char filename[], ListaDescritores ListaD){
    ListaRanking
        ListaR = NULL;
    float
        *hist;

    hist = BuscaHistograma(filename, ListaD);
    if(hist == NULL){
        printf("Imagem nao encontrada na base de dados!\n");
        exit(1);
    }
    while(ListaD->prox != NULL){
        if(strcmp(ListaD->filename, filename) != 0)
            ListaR = InsereNoRanking(ListaR, DistanciaHistogramas(hist, ListaD->hist), ListaD->filename);
        ListaD = ListaD->prox; 
    }
    return ListaR;
}

/*-----------------------------------------------------------------------------------*/

int main(){
    ListaDescritores
        ListaD;
    ListaRanking
        ListaR;
    char
        arquivo[512];

    printf("Entre com o nome do arquivo texto com a base de arquivos de imagem, (imgens localizadas no mesmo diretorio deste executavel):");
    scanf(" %[^\n]", arquivo);
    ListaD = CriaListaDescritores(arquivo);
    printf("Entre com o nome da imagem de busca (uma imagem entre as adicionadas atraves do arquivo texto):");
    scanf(" %[^\n]", arquivo);
    ListaR = ComparaDistancias(arquivo, ListaD);
    ImprimeRanking(ListaR);
    LiberaDescritores(&ListaD);
    LiberaRanking(&ListaR);
    return 0;
}
