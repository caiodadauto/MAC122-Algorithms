#include<stdio.h>
#include<stdlib.h>

void subSeq(int *s, int k, int m, int n){
    int
        i;

    if (m <= n){
        s[k + 1] = m;
        for(i = 1; i <= k + 1; i++)
            printf("%d  ", s[i]);
        printf("\n");
        subSeq(s, k + 1, m + 1, n);
        subSeq(s, k, m + 1, n);
    }
}

int main(){
    int
        *s,
        n;

    printf("entre com n:");
    scanf("%d", &n);
    s = (int *)malloc(sizeof(int) * (n + 1));
    subSeq(s, 0, 1, n);
    free(s);
    return 0;
}
