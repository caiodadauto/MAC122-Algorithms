#include<stdio.h>
#include<stdlib.h>

void invertido(int n){
    if(n / 10 == 0)
        return;
    printf("%d", n % 10);
    invertido(n / 10);
}

int main(){
    int
        n;

    scanf("%d", &n);
    invertido(n);
    return 0;
}
