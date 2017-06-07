#include <stdio.h>
#include <stdlib.h>

void InvertePalavra(char str[], int tam){
    int
        j,
        k,
        final, /*Posicao final da palavra*/
        inicial;/*Posicao inicial da palavra*/
    char
        *temp;

    temp = (char *)malloc(tam * sizeof(char));
    for(k = 0; k <= tam; k++)
        temp[k] = str[k];

    for(k = 0; temp[k] == ' '; k++);
    while(temp[k] != '\0') {
        inicial = k;
        for(final = k; temp[final] != ' ' && temp[final] != '\0'; final++);
        for(j = final - (inicial + 1); j >= 0; k++, j--) {
            str[k] = temp[inicial + j];
        }
        for(; temp[k] == ' '; k++);
    }

    free(temp);
}

int main() {
    char
        str[100];
    int
        i;

    printf("Entre com uma string: ");
    scanf("%[^\n]", str);
    for(i = 0; str[i] != '\0'; i++);
    InvertePalavra(str, i);
    printf("%s\n", str);

    return 0;
}
