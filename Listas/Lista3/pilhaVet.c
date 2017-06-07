#define MAX 10000

typedef struct _RegPilha{
    TipoDado
        v[MAX];
    int
        topo;
} RegPilha;

typedef RegPilha * Pilha;

Pilha CriaPilha(){
    Pilha
        p;

    p = (Pilha)calloc(1, sizeof(RegPilha));
    if(p == NULL)
        exit(-1);

    p->topo = 0;
    return p;
}

void LiberaPilha(Pilha p){
    free(p);
}

char PilhaVazia(Pilha p){
    return (p->topo == 0);
}

void Empilha(Pilha p, TipoDado x){
    if(p->topo == MAX)
        exit(-1);

    p->vet[p->topo] = x;
    p->topo++;
}

TipoDado Desempilha(Pilha p){
    if(p->topo == 0)
        exit(-1);

    p->topo--;
    return (p->vet[p->topo]);
}
