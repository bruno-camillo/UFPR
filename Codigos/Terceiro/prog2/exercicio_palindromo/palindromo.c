#include <stdio.h>
#include <string.h>
#include "tipo_deque.h"

int main() {
    char str[100];
    deque d;

    printf("Digite uma string: ");
    // Lê a string do usuário, garantindo que não exceda o tamanho do buffer
    fgets(str, sizeof(str), stdin);
    // Remove o caractere de nova linha adicionado pelo fgets
    str[strcspn(str, "\n")] = '\0'; 
    
    inicializar_deque(&d);

    // Insere os caracteres da string no deque
    for (size_t i = 0; i < strlen(str); i++) {
        inserir_fim(&d, str[i]);
    }

    // Verifica se a string é um palíndromo
    // Assume que é um palíndromo até provar o contrário
    int eh_palindromo = 1; 
    while (!esta_vazio(&d)) {
        if (obter_inicio(&d) != obter_fim(&d)) {
            // Não é um palíndromo
            eh_palindromo = 0; 
            break;
        }
        remover_inicio(&d);
        if(!esta_vazio(&d)) 
            // Verifica se o deque não está vazio antes de remover o fim
            remover_fim(&d);
    }

    if (esta_vazio(&d)) {
        printf("A string é vazia.\n");
    } else {
        if (eh_palindromo) {
            printf("A string '%s' é um palíndromo.\n", str);
        } else {
            printf("A string '%s' não é um palíndromo.\n", str);
        }
    }

    liberar_deque(&d);
    return 0;
}