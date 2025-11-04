#include <stdio.h>
#include <stdlib.h>

void preencheVetor (int *v, int n) {
    for (int i = 0; i < n; i++)
        scanf ("%d", &v[i]);
}

int buscaNoVet (int *v, int tam, int n) {
    if (tam == 0)
        return -1;
    if (v[tam] == n)
        return tam;
    return buscaNoVet(v, tam - 1, n);
}

int main() {
    int tam;
    scanf ("%d", &tam);

    int *v = malloc (sizeof(int) * tam);

    preencheVetor(v, tam);

    int n;
    scanf ("%d", &n);

    int x = buscaNoVet (v, tam, n);
    if (x == -1)    
        printf ("O elemento nao existe no vetor\n");
    else
        printf ("O elemento esta na posicao %d do vetor\n", x);

    return 0;
}