#include<stdio.h>
#include<stdlib.h>

int analisa(int x[], int n){
    static int
        i = -1;

    if(x[n] == x[n - 1] && i == -1){
        if(n == 1)
            return 2;
        else
            return analisa(x, n - 1);
    }
    else{
        if(x[n] >= x[n - 1]){
            if(i == 0 && x[n] != x[n - 1])
                return 0;
            if(n == 1)
                return 1;
            if(i == -1)
                i = 1;
            return analisa(x, n - 1);
        }
        else{
            if(i == 1 && x[n] != x[n - 1])
                return 0;
            if(n == 1)
                return 3;
            if(i == -1)
                i = 0;
            return analisa(x, n - 1);
        }
    }
}

int main(){
    int
        x[] = {1,1,1,1,1,1,3,1,1};
    int
        n = 9;

    printf("%d\n", analisa(x, n - 1));
    return 0;
}
