#include<stdio.h>
#include<stdlib.h>

/*void piramede(int *s, int k, int m, int n){
    int
        i;

    if(m <= n){
        s[k + 1] = m;
        for(i = k + 1; i >= 0; i--)
            printf("%d", s[i]);
        printf("\n");
        piramede(s, k + 1, m + 1, n);
    }
}*/

void piramede(int n){
    int
        j;
        
    if(n > 0)
        piramede(n - 1);
    for(j = n; j >= 1; j--)
        printf("%d  ", j);
    printf("\n");
}

int main(){
    int
        n;
        /**s;*/

    scanf("%d", &n);
    /*s = (int *)malloc(sizeof(int) * n);
    piramede(s, -1, 1, n);*/
    piramede(n);
    /*free(s);*/
    return 0;
}
