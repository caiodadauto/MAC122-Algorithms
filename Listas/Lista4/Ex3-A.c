#include<stdio.h>
#include<stdlib.h>

int conta(int n){
    if(n != 0){
        return 1 + conta(n/10);
    }
    return 0;
}

int main(){
    int
        n;

    scanf("%d", &n);
    printf("%d\n", conta(n));
    return 0;
}
