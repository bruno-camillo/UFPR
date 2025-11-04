#include <stdio.h>
#include <stdlib.h>

void preencheVetor (int *v, int n) {
    for (int i = 0; i < n; i++)
        scanf ("%d", &v[i]);
}

int minimoVet (int *v, int n) {
    if (n == 1)
        return 0;
    int m = minimoVet (v, n-1);
    if (v[n] <= v[m])
        m = n;
    return m;
}

int main() {
    int n = 10;
    int *v = malloc (sizeof(int) * n);

    preencheVetor (v, n);

    printf ("indice do elemento de menor valor: %d\n", minimoVet(v, n) );
    printf ("O menor elemento eh: %d", v[minimoVet(v,n)]);

    return 0;
}