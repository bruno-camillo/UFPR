#include <stdio.h>
#include <stdlib.h>

int fatorial (int n) {
    if (n == 0)
        return 1;
    return n * fatorial(n-1);
}

int main () {
    int n;
    scanf ("%d", &n);

    printf ("O valor do fatorial de %d eh: %d\n", n, fatorial(n) );

    return 0;
}