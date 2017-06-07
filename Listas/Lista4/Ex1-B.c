#include<stdio.h>
#include<stdlib.h>

float media(float x[], int n){
    if(n == 1)
        return x[n - 1];
    return (media(x, n - 1) * (n - 1) + x[n - 1])/n;
}

int main(){
    float
        x[100];
    int
        i,
        n = 8;

    for(i = 0; i < 8; i++)
        scanf("%f", &x[i]);
    printf("%f\n", media(x, n));
    return 0;
}
