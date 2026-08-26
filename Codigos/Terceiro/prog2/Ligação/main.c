#include <stdio.h>

int main() {
    int a, b, soma; 

    printf("Digite o primeiro número: ");
    scanf("%d", &a);

    printf("Digite o segundo número: ");
    scanf("%d", &b);

    soma = a + b;

    printf("A soma de %d e %d é: %d\n", a, b, soma);
    
    return 0;
}