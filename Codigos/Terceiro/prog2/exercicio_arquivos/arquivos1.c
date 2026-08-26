#include <stdio.h>
#include <stdlib.h>

int main() {
    char frase[200];
    FILE* file = fopen("teste.txt", "w");

    printf("Digite a frase que deseja inserir no arquivo: ");
    fgets(frase, sizeof(frase), stdin);

    if (file != NULL) {
        fprintf(file, frase);
        fclose(file);
    }

    return 1;
}