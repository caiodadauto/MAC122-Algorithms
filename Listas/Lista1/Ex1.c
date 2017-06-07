#include <stdio.h>
#include <stdlib.h>

void InverteString(char str[], int tam){
    int
        i;
    char
        *temp;

    temp = (char *)malloc(tam * sizeof(char));
    for(i = 0; i <= tam; i++)
        temp[i] = str[i];
    for(i = 0; i < tam; i++)
        str[i] = temp[tam - (i + 1)];

    free(temp);
}

int main() {
    char
        str[100];
    int
        i;

    printf("Entre com uma string: ");
    scanf(" %[^\n]", str);
    for(i = 0; str[i] != '\0'; i++);
    InverteString(str, i);
    printf("%s\n", str);

    return 0;
}
