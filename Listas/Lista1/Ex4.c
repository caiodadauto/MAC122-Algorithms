#include <stdio.h>
#include <stdlib.h>

void ProcuraEmail(char dest[], char str[]){
    int
        inicial,
        final,
        k = 0,
        j = 0,
        i = 0;

    while(str[i] != '\0'){
        for(; str[i] != '@' && str[i] != '\0'; i++);
        for(final = i; str[final] != ' ' && str[final] != ',' && str[final] != '\0'; final++);
        for(inicial = i; str[inicial] != ' ' && inicial != 0; inicial--);
        if(str[inicial] == ' ')
            inicial++;
        if(final != inicial && final != i && inicial != i) {
            for(j = inicial; j < final; j++, k++){
                dest[k] = str[j];
            }
            dest[k] = '\n'; 
            i = final;
            k++;
        }
    }
    dest[k] = '\0';
}

int main() {
    char
        dest[500],
        str[500];

    printf("Entre com uma string: ");
    scanf("%[^\n]", str);
    ProcuraEmail(dest, str);
    printf("%s\n%s", str, dest);
    return 0;
}
