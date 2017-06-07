typedef struct _RegPilha{
    TipoDado
        dado;
    struct _RegPilha
        *prox;
} RegPilha;

typedef RegPilha * Pilha;

typedef enum boolean {false, true} bool;

Pilha AlocaPilha(){
    Pilha
        q;

    q = (Pilha)calloc(1, sizeof(RegPilha));
    if(q == NULL)
        exit(-1);
    return q;
}

Pilha CriaPilha(){
    Pilha
        p;

    p = AlocaPilha();
    p->prox = NULL;
    return p;
}

void LiberaPilha(Pilha p){
    Pilha
        q;

    while(p != NULL){
        q = p;
        p = p->prox;
        free(q);
    }
}

bool PilhaVazia(Pilha p){
    return (p->prox == NULL);
}

void Empilha(Pilha p, TipoDado x){
    Pilha 
        q;

    q = AlocaPilha();
    q->dado = x;
    q->prox = p->prox;
    p->prox = q;
}

TipoDado Desempilha(Pilha p){
    TipoDado
        x;
    Pilha
        q;
    
    if(p->prox == NULL)
        exit(-1);

    q = p->prox;
    x = q->dado;
    p->prox = q->prox;
    free(q);
    return x;
}
