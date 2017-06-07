#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct _Monomio{
    float
        coef;
    int
        exp;
    struct _Monomio
        *prox;
} Monomio;

typedef Monomio * Polinomio;

Polinomio AlocaMonomio(){
    Polinomio
        p;

    p = (Polinomio)malloc(sizeof(Monomio));
    if(p == NULL){
        printf("Falta de memoria!\n");
        exit(1);
    }
    return p;
}

Polinomio PolinomioNulo(){/*Nó cabeça*/
    Polinomio
        p;

    p = AlocaMonomio();
    p->exp = -1;
    p->coef = 0.0;
    p->prox = p;
    return p;
}

void InsereMonomio(Polinomio p, int exp, float coef){
    Polinomio
        ant,
        dep,
        q;

    if(coef == 0)
        return;
    q = AlocaMonomio();
    q->coef = coef;
    q->exp = exp;
    ant = p;
    dep = p->prox;
    while(dep->exp > exp){
        ant = dep;
        dep = dep->prox;
    }
    q->prox = dep;
    ant->prox = q;
}

void RemoveAposMonomio(Polinomio p){
    Polinomio
        q;

    q = p->prox;
    p->prox = q->prox;
    free(q);
}

void LiberaPolinomio(Polinomio p){
    while(p != p->prox)
        RemoveAposMonomio(p);
    free(p);
}

float Valor(Polinomio p, float x){
    Polinomio
        q;
    float
        soma = 0;

    if(p == p->prox){
        return 0;
    }
    
    q = p->prox;
    do{
        soma += q->coef * pow(x, q->exp);
        q = q->prox;
    }
    while(q != p);
    return soma;
}

Polinomio Derivada(Polinomio p){
    Polinomio
        d,
        q;
    
    d = PolinomioNulo();
    q = p->prox;
    do{
        InsereMonomio(d, q->exp - 1, q->exp * q->coef);
        q = q->prox;
    }
    while(q != p);
    return d;   
}

Polinomio DerivadaSegunda(Polinomio p){
    Polinomio
        d,
        ds;

    d = Derivada(p);
    ds = Derivada(d);
    LiberaPolinomio(d);
    return ds;
}

Polinomio CriaPolinomio(char expr[]){
    Polinomio
        p;
    int 
        exp,
        r,
        n,
        nn;
    float
        coef,
        sinal = 1.0;
    char 
        c;
 
    nn = 0;
    p = PolinomioNulo();
    while(1){
        r = sscanf(expr+nn," %f * x ^ %d %n",&coef, &exp, &n);
        if(r == 0 || r == EOF) 
            break;
        nn += n;
 
        InsereMonomio(p, exp, sinal * coef);
     
        r = sscanf(expr+nn,"%c %n", &c, &n);
        if(r == EOF || r == 0)
            break;
        nn += n;
 
        if(c == '-')
            sinal = -1.0;
        else
            sinal = 1.0;
    }
  return p;
}

void ImprimePolinomio(Polinomio p){
    Polinomio
        t;
   
    t = p->prox;
    while(t != p){
        printf("%.2f*x^%d",t->coef,t->exp);
        t = t->prox;
        if(t != p){
            if(t->coef >= 0.0)
                printf(" + ");
            else
                printf(" ");
        }
    }
    printf("\n");
}

int main(){
    Polinomio 
        p,
        q,
        r;
 
    p = CriaPolinomio("5.0*x^3 -4.0*x^1 + 2.0*x^0");  
    ImprimePolinomio(p);
 
    q = CriaPolinomio("  8.0*x^4 + 2.0*x^3 + 4.0*x^1");
    ImprimePolinomio(q);
 
    r = DerivadaSegunda(q);
    ImprimePolinomio(r);

    printf("Valor: %f", Valor(p, 1.7));

    LiberaPolinomio(p);
    LiberaPolinomio(q);
    LiberaPolinomio(r);
    return 0;
}
