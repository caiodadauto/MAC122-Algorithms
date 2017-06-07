#include<stdio.h>
#include<stdlib.h>

struct Reg{
    int
        n;
    struct Reg
        *prox;
};

struct Reg *aloca(){
    struct Reg
        *t;

    t = (struct Reg *)malloc(sizeof(struct Reg));
    if(t == NULL)
        exit(1);
    return t;
}

void libera(struct Reg *p){
    struct Reg
        *t;

    while(p->prox != NULL){
        t = p;
        p = p->prox;
        free(t);
    }
    free(p);
}

void removeReg(struct Reg **p){
    struct Reg
        *t;

    if(*p == NULL)
        exit(1);
    t = *p;
    *p = (*p)->prox;
    free(t);
}

void insere(struct Reg **p, int n){
    struct Reg
        *t;

    t = aloca();
    t->n = n;
    if(*p == NULL){
        *p = t;
        t->prox = NULL;
    }
    else{
        *p = t;
        t = (*p)->prox;
    }
}

struct Reg *decrescente(int n){
    struct Reg
        *t;
    t = aloca();
    t->n = n;
    if(n == 1){
        t->prox = NULL;
        return t;
    }
    t->prox = decrescente(n - 1);
    return t;
}

struct Reg *inverte(struct Reg *p){
    struct Reg
        *q,
        *t;

    if(p->prox == NULL){
        return p;
    }
    t = inverte(p->prox);
    q = t;
    while(q->prox != NULL)
        q = q->prox;
    q->prox = p;
    p->prox = NULL;
    return t;
}

int main(){
    struct Reg
        *t,
        *p;
    int
        n;

    scanf("%d", &n);
    p = decrescente(n);
    t = p;
    do{
        printf("%d  ", t->n);
        t = t->prox;
    }while(t != NULL);
    printf("\n");
    p = inverte(p);
    t = p;
    do{
        printf("%d  ", t->n);
        t = t->prox;
    }while(t != NULL);
    printf("\n");
    libera(p);
    return 0;
}
