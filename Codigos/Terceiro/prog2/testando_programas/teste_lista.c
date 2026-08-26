#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lista.h"

int main () {
    struct lista *l = lista_cria();
    int chave;

    // Testa se a lista foi criada corretamente
    printf("TESTE: Lista criada corretamente\n");
    assert (lista_vazia(l) == 1);
    assert (lista_tamanho(l) == 0);
    lista_imprime(l);

    // Testa inserção no início da lista
    printf("TESTE: Inserção no início da lista\n");

    printf("Inserindo 1\n");
    assert (lista_insere_inicio(l, 1) == 1);
    printf("Inserindo 2\n");
    assert (lista_insere_inicio(l, 2) == 1);
    printf("Inserindo 3\n");
    assert (lista_insere_inicio(l, 3) == 1);
    lista_imprime(l);

    // Testa se os elementos foram inseridos corretamente
    assert (lista_vazia(l) == 0);
    assert (lista_tamanho(l) == 3);

    // Testa remoção do início da lista
    printf("TESTE: Remoção do início da lista\n");
    printf("Removendo 3\n");
    assert (lista_remove_inicio(l, &chave) == 1);
    assert (chave == 3);
    lista_imprime(l);

    // Testa remoção do final da lista
    printf("TESTE: Remoção do final da lista\n");
    printf("Removendo 1\n");
    assert (lista_remove_fim(l, &chave) == 1);
    assert (chave == 1);
    lista_imprime(l);

    // Testa remoção do início da lista novamente
    printf("TESTE: Remoção do início da lista novamente\n");
    printf("Removendo 2\n");
    assert (lista_remove_inicio(l, &chave) == 1);
    assert (chave == 2);
    lista_imprime(l);

    // Testa se a lista está vazia após as remoções
    assert (lista_vazia(l) == 1);
    assert (lista_tamanho(l) == 0);

    // Testa remoção de uma lista vazia
    printf("TESTE: Remoção de uma lista vazia\n");
    assert (lista_remove_inicio(l, &chave) == 0);
    assert (lista_remove_fim(l, &chave) == 0);

    lista_destroi(&l);

    // Teste de inserção ordenada de 10 elementos
    printf("TESTE: Inserção ordenada de 10 elementos\n");
    for (int i = 1; i <= 10; i++) {
        printf("Inserindo %d\n", i);
        assert (lista_insere_ordenado(l, i) == 1);
    }
    lista_imprime(l);

    // Testa se os elementos foram inseridos corretamente    
    assert (lista_vazia(l) == 0);
    assert (lista_tamanho(l) == 10);

    // Testa remoção ordenada de um elemento do meio da lista
    printf("TESTE: Remoção ordenada de um elemento do meio da lista\n");
    printf("Removendo 5\n");
    assert (lista_remove_ordenado(l, 5) == 1);
    lista_imprime(l);

    return 0;
}