#include<stdio.h>
#include<stdlib.h>

int dividi(int a, int b){
    if(b == 0)
        return 1;
    return a/b;
}

int conta(int a, int x[], int n){
    if(n < 0)
        return 0;
    if(x[n] == a)
        return dividi(x[n], a) + conta(a, x, n - 1);
    return conta(a, x, n - 1);

}

int moda(int x[], int n){
    int
        m;
    static int
        i = 0;

    ++i;
    if(n == 1){
        if(x[n] == x[n - 1])
            return x[n];
        if(conta(x[n], x, i) < conta(x[n - 1], x, i))
            return x[n - 1];
        return x[n];
    }
    m = moda(x, n - 1);
    if(x[n] == m)
        return m;
    if(conta(x[n], x, i) > conta(m, x, i))
        return x[n];
    return m;
}

int main(){
    int
        x[] = {1,1,7,1,1,3,0,2,9};
    int
        n = 9;

    printf("%d\n", moda(x, n - 1));
    return 0;
}
