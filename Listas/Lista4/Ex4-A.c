#include<stdio.h>
#include<stdlib.h>

float potencia(float x, int n){
    if(n == 0)
        return 1;
    if(n > 0)
        return x * potencia(x, n - 1);
    return 1.0/x * potencia(x, n + 1); 
}

int main(){
    float
        x;
    int
        n;

    scanf("%f%d", &x, &n);
    printf("%f\n", potencia(x, n));
    return 0;
}
