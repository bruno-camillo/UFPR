#include <stdio.h>
#include <stdlib.h>

void Troca (int *v, int i, int j) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int buscaSequencial (int *v, int x, int n) { 
    if (n < 0)
        return -1;
    if (x >= v[n])
        return n;
    return buscaSequencial(v, x, n-1);
}

int * Insere (int *v, int n) {
    int p = buscaSequencial (v, v[n], n-1);
    int i = n;

    while (i > p + 1) {
        Troca (v, i, i-1);
        i--;
    }

    return v;
}

int * InsertionSort (int *v, int n) {
    if (n <= 0)
        return v;

    InsertionSort(v, n - 1);
    Insere(v, n - 1);
   
    return v;   
}

int main() {
    int n;
    scanf("%d", &n);

    int *v = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    v = InsertionSort(v, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}