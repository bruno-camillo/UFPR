#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char string[100];
    char delimitador[] = ",";
    char * resultado;
    int i = 2;

    // "scanf" da string
    fgets(string, sizeof(string), stdin);

    resultado = strtok(string, delimitador);
    printf("Coluna 1: %s\n", resultado);

    resultado = strtok(NULL, delimitador);

    while (resultado != NULL) {
        printf("Coluna %d:%s\n", i, resultado);
        resultado = strtok(NULL, delimitador);
        i++;
    }

    return 1;
}