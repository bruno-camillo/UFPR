#include <stdio.h>
#include <string.h>
#include <math.h>

void operacao (char *operador, double *vetor, double (*func)(double)) {
    printf("Resultado da operação %s: ", operador);
    for (int i = 0; i<5; i++)
        printf("%f ", func(vetor[i]));
    printf("\n");
}

int main () {
    char operador[10];
    double vetor[5] = {4, 9, 16, 25, 36};

    printf("Digite o operador: ");
    scanf("%s", operador);

    if (!strcmp(operador, "sqrt"))
        operacao(operador, vetor, sqrt);
    else if (!strcmp(operador, "floor"))
        operacao(operador, vetor, floor);
    else if (!strcmp(operador, "cbrt"))
        operacao(operador, vetor, cbrt);
    else 
        printf("Operador desconhecido\n");
    
}