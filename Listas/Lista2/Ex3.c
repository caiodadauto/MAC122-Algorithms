#include<stdio.h>
#include<stdlib.h>

typedef struct _Reg{
    int
        n;
    struct _Reg
        *prox;
} Reg;

Reg *AlocaNo(){
    Reg
        *q;

    q = (Reg *)malloc(sizeof(Reg));
    return q;
}

void InsereApos(Reg **l, int n){
    Reg
        *q;

    q = AlocaNo();
    q->n = n;
    q->prox = *l;
    *l = q;
}

void RemoveApos(Reg **l){
    Reg
        *t;

    t = *l;
    if(t != NULL){
        *l = t->prox;/**(l)->prox == *(*t).prox*/
        free(t);
    }
}

void Imprime(Reg *l){
    while(l != NULL){
        printf("%d ", l->n);
        l = l->prox;
    }
    printf("\n");
}

/*Reg *RemoveNum(Reg *l, int a){
    Reg
        *inic;

    while(l->n == a && l != NULL){
        RemoveApos(&l);
    }
    if(l != NULL)
        inic = l;
    if(l == NULL){
        printf("UU\n");
        return NULL;
    }
    while(l->prox != NULL){
        if(l->prox->n == a)
            RemoveApos(&(l->prox));/*É MTO diferente passar como parametro &(l->prox) ou l = l->prox, &l
        else
            l = l->prox;
    }
    return inic;
}*/

Reg *RemoveNum(Reg *p, int a){
	Reg *q;
	Reg **b;
	
	q = AlocaNo();
	q->prox = p;
	b = &(q->prox);
	while(q->prox != NULL){
		if(q->prox->n == a)
			RemoveApos(&q);
		else
			q = q->prox;
	}
	return *b;
}

int main(){
    int
        n,
        i;
    Reg
        *q = NULL;

    for(i = 0; i < 5; i++){
        scanf("%d", &n);
        InsereApos(&q, n);
    }
    q = RemoveNum(q, 5);
    if(q == NULL)
        printf("Todos os elementos de são iguais a 5\n");
    else
        Imprime(q);
    return 0;
}
