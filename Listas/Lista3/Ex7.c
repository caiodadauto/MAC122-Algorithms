typedef struct _RegFilaDupla{
    TipoDado
        dado;
    struct _RegFilaDupla
        *prox,
        *ante;
}RegFilaDupla;

typedef RegFilaDupla * FilaDupla;

typedef enum boolean {false, true} bool;

FilaDupla CriaFilaDupla(){
    FilaDupla
        f;

    f = (FilaDupla)malloc(sizeof(RegFilaDupla));
    if(f == NULL)
        exit(-1);
    f->dado = -1;
    f->prox = f;
    f->ante = f;
    return f;
}

void LiberaFilaDupla(FilaDupla f){
    FilaDupla
        t,
        q;

    q = f->prox;
    while(q != f){
        t = q;
        q = q->prox;
        free(t);
    }
    free(f);
}

bool FilaDuplaVazia(FilaDupla f){
    return (f->prox == f);
}

void InsereFrenteFilaDupla(FilaDupla *f, TipoDado x){
    FilaDupla
        q;

    q = (FilaDupla)malloc(sizeof(RegFilaDupla));
    q->dado = x;
    if((*f)->prox == *f){
        q->prox = (*f)->prox;
        q->ante = (*f)->ante;
        (*f)->prox = q;
        (*f)->ante = q;
        *f = q;
    }
    else{
        q->prox = (*f)->prox->prox;
        q->ante = (*f)->prox
        (*f)->prox->prox->ante = q;
        (*f)->prox->prox = q;
    }
}

void InsereFimFilaDupla(FilaDupla *f, TipoDado x){
    FilaDupla
        q;

    q = (FilaDupla)malloc(sizeof(RegFilaDupla));
    q->dado = x;
    q->prox = (*f)->prox;
    q->ante = (*f);
    (*f)->prox->ante = q;
    (*f)->prox = q;
    *f = q;
}

TipoDado RemoveFrenteFilaDlupa(FilaDupla *f){
    FilaDupla
        q;

    if((*f)->prox == (*f))
        exit(-1);
    q = (*f)->prox->prox;
    x = (*f)->prox->prox->dado;
    (*f)->prox->prox = q->prox;
    q->prox->ante = (*f)->prox;
    if(*f == q)
        *f = (*f)->prox;
    free(q);
    return x;
}

TipoDado RemoveFimFilaDlupa(FilaDupla *f){
    FilaDupla
        q;

    if((*f)->prox == (*f))
        exit(-1);
    q = (*f);
    x = (*f)->dado;
    (*f)->ante->prox = (*f)->prox;
    (*f)->prox->ante = (*f)->ante;
    *f = (*f)->ante;
    free(q);
    return x;
}
