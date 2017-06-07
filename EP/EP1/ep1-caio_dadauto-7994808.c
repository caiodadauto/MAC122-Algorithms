/* EP01(parte 1) - Turma 01 Paulo Miranda
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

void Comandos();
void LiberaMatriz(int **M, int m, int n);
void GravaImagem(char filename[], int **M, int m, int n);
void OrdenacaoInsercao(int V[], int n);
void CopiaMatriz(int **M, int **A, int m, int n);
int **Coparacao(int **M, int m, int n, int *linha, int *coluna);
int **AlocaMatriz(int m, int n);
int **AbreImagem(char filename[], int *m, int *n);
int **MatrizVizinhanca(int **M, int am, int an, int m, int n, int p);
int **SubtraiMatriz(int **A, int **B, int m, int n);
int **rotacao(int **M, int *m, int *n);
int **corte(int **M, int *m, int *n, int xsup, int ysup, int xinf, int yinf);
int *LinearizaValoresPositivos(int **M, int p, int *num);
int TamanhoJanela(int *p);
int ValorK(int *k);
int ValorMaximo(int **M, int m, int n);
int MinimoVizinhanca(int **M, int p);
int MedianaVizinhanca(int **M, int p);
void rebatimentoVertical(int **M, int m, int n);
void rebatimentoHorizontal(int **M, int m, int n);
void negativo(int **M, int m, int n);
void filtroErosao(int **M, int m, int n, int larguraJanela);
void filtroDilatacao(int **M, int m, int n, int larguraJanela);
void filtroMediana(int **M, int m, int n, int larguraJanela);
void filtroMedia(int **M, int m, int n, int larguraJanela);
void filtroBorda1(int **M, int m, int n, int larguraJanela, int k);
void filtroBorda2(int **M, int m, int n, int larguraJanela, int k);
void filtroBorda3(int **M, int m, int n, int larguraJanela, int k);

/*---------------------------------------------------------------------------------
 *****************************FUNCOES AUXILIARES***********************************
 --------------------------------------------------------------------------------*/

void Comandos(){
    printf("\nOpcoes de comandos:\n");
    printf("\tc\t->\tCarregar um arquivo;\n");
    printf("\tt\t->\tExibicao na tela;\n");
    printf("\tn\t->\tNegativo;\n");
    printf("\tr\t->\tRotacao;\n");
    printf("\tv\t->\tEspelhamento vertical;\n");
    printf("\th\t->\tEspelhamento horizontal;\n");
    printf("\tx\t->\tCorte;\n");
    printf("\te\t->\tFiltro da erosao;\n");
    printf("\td\t->\tFiltro da dilatacao;\n");
    printf("\tm\t->\tFiltro da mediana;\n");
    printf("\tM\t->\tFiltro da media;\n");
    printf("\t1\t->\tFiltros de bordas 1;\n");
    printf("\t2\t->\tFiltros de bordas 2;\n");
    printf("\t3\t->\tFiltros de bordas 3;\n");
    printf("\tg\t->\tSalva imagem em arquivo separado;\n");
    printf("\tC\t->\tComparacao;\n");
    printf("\ta\t->\tAjuda;\n");    printf("\ts\t->\tSair do programa;\n");
}

int TamanhoJanela(int *p){
    printf("Insira o tamanho (numero impar) da janela de vizinhanca:");
    scanf("%d", p);
    if(*p % 2 == 0){
        printf("Numero par, o tamnho da janela deve ser impar!\n");
        return 0;
    }
    return 1;
}

int ValorK(int *k){
    printf("Insira o valor de \"k\" (0 <= k <= 255):");
    scanf("%d", k);
    if(*k < 0 || *k > 255){
        printf("Valor invalido de k, 0 <= k <= 255!\n");
        return 0;
    }
    return 1;
}

int **AlocaMatriz(int m, int n){
    int
        i,
        **A;

    A = (int **)malloc(m * sizeof(int *));
    for(i = 0; i < m; i++)
        A[i] = (int *)malloc(n * sizeof(int));
    return A;
    
}

int *LinearizaValoresPositivos(int **M, int p, int *num){
    int
        i,
        j,
        k = 0,
        *V;

    for(i = 0; i < p; i++){
        for(j = 0; j < p; j++){
            if(M[i][j] >= 0)
                ++*(num);
        }
    }
    V = (int *)malloc(*num * sizeof(int));
    for(i = 0; i < p; i++){
        for(j = 0; j < p; j++){
            if(M[i][j] >= 0){
                V[k] = M[i][j];
                k++;
            }
        }
    }
    return V;
}

int **MatrizVizinhanca(int **M, int am, int an, int m, int n, int p){
    int
        i,
        j,
        **A;

    A = AlocaMatriz(p, p);
    for(i = 0; i < p; i++){
        for(j = 0; j < p; j++){
            if(am - p/2 + i >= 0 && an - p/2 + j >= 0 && am - p/2 + i < m && an - p/2 + j < n)
                A[i][j] = M[am - p/2 + i][an - p/2 + j];
            else
                A[i][j] = -1;
        }
    }
    return A;
}

void CopiaMatriz(int **M, int **A, int m, int n){
    int
        i,
        j;

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            M[i][j] = A[i][j];
    }
}

int **SubtraiMatriz(int **A, int **B, int m, int n){
    int
        i,
        j,
        **M;

    M = AlocaMatriz(m, n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            M[i][j] = A[i][j] - B[i][j];
    }
    return M;
}

void LiberaMatriz(int **M, int m, int n){
    int
        i;

    for(i = 0; i < m; i++)
        free(M[i]);
    free(M);
}

int **AbreImagem(char filename[], int *m, int *n){
    FILE
        *entrada;
    char
        str[55];
    int
        i,
        j,
        **A;

    strcpy(str, filename);
    strcat(str, ".pgm");
    entrada = fopen(str, "r");
    if(entrada == NULL){
        printf("Arquivo nao encontrado.\n");
        return NULL;
    }
    fseek(entrada, 3, SEEK_SET);
    fscanf(entrada, "%d %d", n, m);
    A = AlocaMatriz(*m, *n);
    fseek(entrada, sizeof(int), SEEK_CUR);
    for(i = 0; i < *m; i++){
        for(j = 0; j < *n; j++)
            fscanf(entrada, "%d", &A[i][j]);
    }
    fclose(entrada);
    printf("Arquivo %s carregado com sucesso!\n", str);
    return A;
}

int ValorMaximo(int **M, int m, int n){
    int
        i,
        j,
        max = 0;

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            if(M[i][j] > max)
                max = M[i][j];
        }
    }
    return max;
}

int MinimoVizinhanca(int **M, int p){
    int
        i,
        j,
        min = 255;

    for(i = 0; i < p; i++){
        for(j= 0; j < p; j++){
            if(M[i][j] < min && M[i][j] >= 0)
                min = M[i][j];
        }
    }
    LiberaMatriz(M, p, p);
    return min;
}

int MedianaVizinhanca(int **M, int p){
    int
        num = 0,
        mediana,
        *V;

    V = LinearizaValoresPositivos(M, p, &num);
    OrdenacaoInsercao(V, num);
    mediana = V[num/2];
    LiberaMatriz(M, p, p);
    free(V);
    return mediana;
}

int MediaVizinhanca(int **M, int p){
    int
        i,
        num = 0,
        media = 0,
        *V;

    V = LinearizaValoresPositivos(M, p, &num);
    for(i = 0; i < num; i++)
        media += V[i];
    media /= num;
    LiberaMatriz(M, p, p);
    free(V);
    return media;
}

void OrdenacaoInsercao(int V[], int n){
    int
        i,
        j,
        aux;

    for(i = 1; i < n; i++){
        aux = V[i];
        for(j = i - 1; j >= 0 && V[j] > aux; j--)
            V[j + 1] = V[j];
        V[j + 1] = aux;
    }
}

void limiarizacao(int **M, int m, int n, int k){
    int
        i,
        j;

    for(i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            if(M[i][j] >= k)
                M[i][j] = 255;
            else
                M[i][j] = 0;
        }
    }
}

void GravaImagem(char filename[], int **M, int m, int n){
    FILE
        *saida;
    char
        str[55];
    int
        i,
        j;

    strcpy(str, filename);
    strcat(str, ".pgm");
    saida = fopen(str, "w");
    fprintf(saida, "P2\n%d %d\n%d\n", n, m, ValorMaximo(M, m, n));
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            fprintf(saida, "%3d\t", M[i][j]);
        fprintf(saida, "\n");
    }
    fclose(saida);
}

int **Coparacao(int **M, int m, int n, int *linha, int *coluna){
    char
        filename[50];
    int
        i,
        j,
        **A = NULL;

    do{
        printf("Entre com o nome do arquivo de imagem a ser comparado (sem extensao): ");
        scanf(" %[^\n]", filename);
        getchar();
        A = AbreImagem(filename, linha, coluna);
    }
    while(A == NULL);
    if(m != *linha || n != *coluna){
        printf("As imagens nao sao iguais!\n");
        return A;
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            if(M[i][j] != A[i][j]){
                printf("As imagens nao sao iguais!\n");
                return A;
            }
        }
    }
    printf("As imagens sao iguais!\n");
    return A;
}

/*---------------------------------------------------------------------------------
 *****************************TRANSFORMACAO****************************************
 --------------------------------------------------------------------------------*/

void negativo(int **M, int m, int n){
    int
        i,
        j;

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            M[i][j] = 255 -M[i][j];
    }
}

int **rotacao(int **M, int *m, int *n){
    int
        i,
        j,
        **A;

    A = AlocaMatriz(*n, *m);
    for(i = 0; i < *m; i++){
        for(j = 0; j < *n; j++)
            A[j][*m - i -1] = M[i][j];
    }
    LiberaMatriz(M, *m, *n);
    i = *n;
    *n = *m;
    *m = i;
    return A;
}

void rebatimentoVertical(int **M, int m, int n){
    int
        i,
        j;

    for(j = 0; j < n/2; j++){
        for(i =0; i < m; i++){
            M[i][j] += M[i][n - 1 - j];
            M[i][n - 1 - j] = M[i][j] - M[i][n - 1 - j];
            M[i][j] =  M[i][j] - M[i][n - 1 - j];
        }
    }
}

void rebatimentoHorizontal(int **M, int m, int n){
    int
        *aux,
        i;

    for(i = 0; i < m/2; i++){
        aux = M[i];
        M[i] = M[m - 1 - i];
        M[m - 1 - i] = aux;
    }
}

int **corte(int **M, int *m, int *n, int xsup, int ysup, int xinf, int yinf){
    int
        incx,
        incy,
        deltax,
        deltay,
        i,
        j,
        **A;

    if(xsup - xinf < 0)
        incx = xsup;
    else
        incx = xinf;
    if(ysup - yinf < 0)
        incy = ysup;
    else
        incy = yinf;

    deltax = abs(xsup - xinf);
    deltay = abs(ysup - yinf);
    A = AlocaMatriz(deltay + 1, deltax + 1);
    for(i = 0; i <= deltay; i++){
        for(j = 0; j <= deltax; j++)
            A[i][j] = M[incy + i][incx + j];
    }
    LiberaMatriz(M, *m, *n);
    *n = deltax + 1;
    *m = deltay + 1;
    return A;
}

/*---------------------------------------------------------------------------------
 *****************************FILTROS**********************************************
 --------------------------------------------------------------------------------*/

void filtroErosao(int **M, int m, int n, int larguraJanela){
    int
        i,
        j,
        **A;

    A = AlocaMatriz(m, n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            A[i][j] = MinimoVizinhanca(MatrizVizinhanca(M, i, j, m, n, larguraJanela), larguraJanela);
    } 
    CopiaMatriz(M, A, m, n);
    LiberaMatriz(A, m, n);
}

void filtroDilatacao(int **M, int m, int n, int larguraJanela){
     int
        i,
        j,
        **B,
        **A;

    A = AlocaMatriz(m, n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            B = MatrizVizinhanca(M, i, j, m, n, larguraJanela);
            A[i][j] = ValorMaximo(B, larguraJanela, larguraJanela);
            LiberaMatriz(B, larguraJanela, larguraJanela);
        }
    }
    CopiaMatriz(M, A, m, n);
    LiberaMatriz(A, m, n);
}

void filtroMediana(int **M, int m, int n, int larguraJanela){
    int
        i,
        j,
        **A;

    A = AlocaMatriz(m, n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            A[i][j] = MedianaVizinhanca(MatrizVizinhanca(M, i, j, m, n, larguraJanela), larguraJanela);
    } 
    CopiaMatriz(M, A, m, n);
    LiberaMatriz(A, m, n);   
}

void filtroMedia(int **M, int m, int n, int larguraJanela){
    int
        i,
        j,
        **A;

    A = AlocaMatriz(m, n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
            A[i][j] = MediaVizinhanca(MatrizVizinhanca(M, i, j, m, n, larguraJanela), larguraJanela);
    } 
    CopiaMatriz(M, A, m, n);
    LiberaMatriz(A, m, n);   
}

void filtroBorda1(int **M, int m, int n, int larguraJanela, int k){
    int
        **S,
        **A;

    A = AlocaMatriz(m, n);
    CopiaMatriz(A, M, m, n);
    filtroDilatacao(A, m, n, larguraJanela);
    filtroErosao(M, m, n, larguraJanela);
    S = SubtraiMatriz(A, M, m, n);
    limiarizacao(S, m, n, k);
    CopiaMatriz(M, S, m, n);
    LiberaMatriz(S, m, n);
    LiberaMatriz(A, m, n);
}

void filtroBorda2(int **M, int m, int n, int larguraJanela, int k){
    int
        **S,
        **A;

    A = AlocaMatriz(m, n);
    CopiaMatriz(A, M, m, n);
    filtroErosao(A, m, n, larguraJanela);
    S = SubtraiMatriz(M, A, m, n);
    limiarizacao(S, m, n, k);
    CopiaMatriz(M, S, m, n);
    LiberaMatriz(S, m, n);
    LiberaMatriz(A, m, n);
}

void filtroBorda3(int **M, int m, int n, int larguraJanela, int k){
    int
        **S,
        **A;

    A = AlocaMatriz(m, n);
    CopiaMatriz(A, M, m, n);
    filtroDilatacao(A, m, n, larguraJanela);
    S = SubtraiMatriz(A, M, m, n);
    limiarizacao(S, m, n, k);
    CopiaMatriz(M, S, m, n);
    LiberaMatriz(S, m, n);
    LiberaMatriz(A, m, n);
}

/*---------------------------------------------------------------------------------
 *****************************FUNCAO PRINCIPAL*************************************
 --------------------------------------------------------------------------------*/

int main (){
    char
        loopUM = 1,
        comando = 'c',
        nomePadrao[50],
        nome[50];
    int
        i,
        j,
        m,
        n,
        p,
        k,
        xsup,
        xinf,
        ysup,
        yinf,
        linha,
        coluna,
        **C,
        **A = NULL;

    while(comando != 's'){
        switch(comando){
            case 'c':
                if(A != NULL)
                    LiberaMatriz(A, m, n);
                do{
                    printf("Entre com o nome do arquivo de imagem a ser carregado (sem extensao): ");
                    scanf(" %[^\n]", nome);
                    getchar();
                    A = AbreImagem(nome, &m, &n);
                }
                while(A == NULL);
                if(loopUM){
                    Comandos();
                    loopUM = 0;
                }
                strcat(nome, "-");
                strcpy(nomePadrao, nome);
            break;

            case 't':
                for(i = 0; i < m; i++){
                    for(j = 0; j < n; j++)
                        printf("%3d\t", A[i][j]);
                    printf("\n");
                }
            break;

            case 'n':
                negativo(A, m, n);
                strcat(nome, "n");
                printf("Negativo da imagem, feito!\n");
            break;

            case 'r':
                A = rotacao(A, &m, &n);
                strcat(nome, "r");
                printf("Rotacao da imagem, feita!\n");
            break;

            case 'v':
                rebatimentoVertical(A, m, n);
                strcat(nome, "v");
                printf("Espelahmento vertical da imagem, feito!\n");
            break;

            case 'h':
                rebatimentoHorizontal(A, m, n);
                strcat(nome, "h");
                printf("Espelhamento horizontal da imagem, feito!\n");
            break;

            case 'x':
                printf("Entre com os seguintes valores para que seja efetuado o corte:\n\tx superior:");
                scanf("%d", &xsup);
                printf("\ty superior:");
                scanf("%d", &ysup);
                printf("\tx inferior:");
                scanf("%d", &xinf);
                printf("\ty inferior:");
                scanf("%d", &yinf);
                if(xinf > n - 1 || xsup > n - 1 || yinf > m - 1 || ysup > m - 1 || xsup < 0 || xinf < 0 || ysup < 0 || yinf < 0){
                    printf("Limites invalidos!\n");
                    break;
                }
                A = corte(A, &m, &n, xsup, ysup, xinf, yinf);
                strcat(nome, "x");
                printf("Corte da imagem, feito!\n");
            break;

            case 'e':
                if(!TamanhoJanela(&p))
                    break;
                filtroErosao(A, m, n, p);
                strcat(nome, "e");
                printf("Filtro de erosao, feito!\n");
            break;

            case 'd':
                if(!TamanhoJanela(&p))
                    break;
                filtroDilatacao(A, m, n, p);
                strcat(nome, "d");
                printf("Filtro de dilatacao, feito!\n");
            break;

            case 'm':
                if(!TamanhoJanela(&p))
                    break;
                filtroMediana(A, m, n, p);
                strcat(nome, "m");
                printf("Filtro de mediana, feito!\n"); 
            break;

            case 'M':
                if(!TamanhoJanela(&p))
                    break;
                filtroMedia(A, m, n, p);
                strcat(nome, "M");
                printf("Filtro de media, feito!\n"); 
            break;

            case '1':
                if(!TamanhoJanela(&p) || !ValorK(&k))
                    break;
                filtroBorda1(A, m, n, p, k);
                strcat(nome, "1");
                printf("Filtro borda 1, feito!\n");
            break;

            case '2':
                if(!TamanhoJanela(&p) || !ValorK(&k))
                    break;
                filtroBorda2(A, m, n, p, k);
                strcat(nome, "2");
                printf("Filtro borda 2, feito!\n");
            break;

            case '3':
                if(!TamanhoJanela(&p) || !ValorK(&k))
                    break;
                filtroBorda1(A, m, n, p, k);
                strcat(nome, "3");
                printf("Filtro borda 3, feito!\n");
            break;

            case 'g':
                if(!strcmp(nome , nomePadrao)){
                    printf("Nao ha alteracoes para serem salvas!\n");
                    break;
                }
                GravaImagem(nome, A, m, n);
                printf("Gravação realizada!\n");
            break;

            case 'C':
                C = Coparacao(A, m, n, &linha, &coluna);
                LiberaMatriz(C, linha, coluna);
            break;

            case 'a':
                Comandos();
            break;
            
            default:
                printf("\nComando invalido!\nDigite \"a\" para ajuda.\n");
            break;

        }
        printf("\nDigite um comando: ");
        scanf(" %c", &comando);
        getchar();
    }
    LiberaMatriz(A, m, n);
    return 0;
}
