#include <stdio.h>
#include <stdlib.h>

int buscaBinaria (int *v, int x, int a, int b) {
    if (a > b)
        return -1;
    
    int m = (a + b) / 2;

    if (x == v[m])
        return m;

    if (x < v[m])
        return buscaBinaria(v, x, a, m - 1);

    return buscaBinaria(v, x, m + 1, b);
}

int main() {
    int a = 0;
    int b;
    scanf("%d", &b);

    int *v = malloc(b * sizeof(int));

    for (int i = 0; i < b; i++) {
        scanf("%d", &v[i]);
    }

    int x;
    scanf("%d", &x);

    int resultado = buscaBinaria(v, x, a, b - 1);
    printf("%d\n", resultado);

    return 0;
}