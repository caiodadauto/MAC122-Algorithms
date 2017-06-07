#include<stdio.h>
#include<stdlib.h>

typedef struct _Reg{
    int
        num;
    struct _Reg
        *prox;
} Reg;

Reg *AlocaNoLista(){
    Reg
        *l;

    l = (Reg *)malloc(sizeof(Reg));
    return l;
}

void InsereApos(Reg **l, int num){
    Reg
        *q;

    q = AlocaNoLista();
    q->num = num;
    q->prox = *l;
    *l = q;
}

/* Para laço com nó cabeça
void InsereApos(Reg *l, int num){
    Reg
        *p;

    p = AlocaNoLista();
    p->num = num;
    p->prox = l->prox;
    l->prox = p;
}*/

/*Serve para ambas (cabeça e sem cabeça) desde que 
 * troque *l por l->prox e claro **l por *l*/
void RemoveApos(Reg **l){
    Reg
        *t;

    t = *l;
    if(t != NULL){
        *l = t->prox;
        free(t);
    }
}

int NumElementos(Reg *l){
    int
        cont;

    for(cont = 1; l->prox != NULL; cont++)
        l = l->prox;
    return cont;
}

void Libera(Reg *l){
    int
        i;

    for(i = NumElementos(l); i > 0; i--)
        RemoveApos(&l);
}

int Pertence(Reg *l, int x){
    while(l != NULL){
        if(l->num == x)
            return 1;
        l = l->prox;
    }
    return 0;
}

Reg *Interseccao(Reg *l, Reg *q){
    Reg
        *r = NULL;

    while(l != NULL){
        if(Pertence(q, l->num))
            InsereApos(&r, l->num);
        l = l->prox;
    }
    return r;
}

void Imprime(Reg *l){
    if(l == NULL){
        printf("Lista Vazia!\n");
        return;
    }
    while(l != NULL){
        printf("%d ", l->num);
        l = l->prox;
    }
    printf("\n");
}

int main(){
    int
        i,
        num;
    Reg
        *r,
        *q = NULL,
        *l = NULL;

    for(i = 0; i < 5; i++){  
        scanf("%d", &num);
        InsereApos(&l, num);
    }
    for(i = 0; i < 6; i++){  
        scanf("%d", &num);
        InsereApos(&q, num);
    }
    r = Interseccao(l, q);
    Imprime(r);
    Libera(l);
    Libera(q);
    Libera(r);
    return 0;
}
