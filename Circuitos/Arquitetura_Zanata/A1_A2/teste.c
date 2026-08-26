#include <stdio.h>

void imprimeVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main () {
    int R[10];
    int A[10];
    int B[10];
    int i = 0;
    int k = 0;

if_1:
    if (i >= 10) {
        goto fim_if_1;
    }
    A[i] = k;
    B[i] = k + 1;
    k += 2;
    i++;
    goto if_1;

fim_if_1:
    i = 0;

if_2:
    if (i >= 10) {
        goto fim_if_2;
    }
    k = A[i] + B[i]; // zera registrador, soma um e dps o outro
    R[i] = k;
    i++;
    goto if_2;

fim_if_2:
    return 0;
}