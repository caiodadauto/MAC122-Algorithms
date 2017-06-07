#include<stdio.h>
#include<stdlib.h>

int conta(int a, int x[], int n){
    if(n < 0)
        return 0;
    if(x[n] == a)
        return x[n]/a + conta(a, x, n - 1);
    return conta(a, x, n - 1);

}

int main(){
    int
        x[] = {1,2,7,2,2,0,3,2,9};
    int
        n = 9;

    printf("%d\n", conta(1, x, n - 1));
    return 0;
}
