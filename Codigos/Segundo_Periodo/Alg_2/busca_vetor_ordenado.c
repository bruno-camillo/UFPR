#include <stdio.h>
#include <stdlib.h>

int buscaSequencial (int *v, int x, int n) { 
    if (n <= 0)
        return -1;
    if (x >= v[n-1])
        return n-1;
    return buscaSequencial(v, x, n-1);
}

int main() {
    int n, x, *v, resultado;

    scanf("%d", &n);
    v = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    scanf("%d", &x);

    resultado = buscaSequencial(v, x, n);

    printf("%d\n", resultado);
    free(v);

    return 0;
}