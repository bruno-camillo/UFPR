#include <stdio.h>

int main() {
    FILE* file = fopen("teste.txt", "r");
    char frase[100];

    if (file == NULL)
        return printf("Erro ao abrir o arquivo");

    fgets(frase, sizeof(frase), file);

    printf("%s", frase);

    fclose(file);

    return 1;
}