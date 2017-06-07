#include <stdio.h>
#include <stdlib.h>

void ReduzEspacos(char dest[], char str[]){
    int
        j = 0,
        i;

    for(i = 0; str[i] == ' '; i++);
    if(i != 0){
        dest[0] = ' ';
        j = 1;
    }
    while(str[i] != '\0'){
        for(; str[i] != ' ' && str[i] != '\0'; i++, j++)
            dest[j] = str[i];
        if(str[i] == ' '){
            dest[j] = ' ';
            j++;
        }
        for(; str[i] == ' '; i++);
    }
    dest[j] = '\0';
}

int main() {
    char
        dest[100],
        str[100];

    printf("Entre com uma string: ");
    scanf("%[^\n]", str);
    ReduzEspacos(dest, str);
    printf("%s\n%s\n", str, dest);

    return 0;
}
