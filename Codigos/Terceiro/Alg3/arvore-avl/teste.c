#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arvbin_busca.h"
#include "arvore-avl.h"

// Função auxiliar para criar e inserir rapidamente no teste
void inserir_teste(arvore *A, int chave) {
    nodo *n;
    assert(nodo_build(&n, chave, NULL));
    avl_insert(A, n);
}

// Função auxiliar para buscar e remover com segurança
void remover_teste(arvore *A, int chave) {
    nodo *n = tree_search(A->raiz, chave);
    if (n != NULL) {
        printf("Removendo chave %d...\n", chave);
        avl_delete(A, n);
    } else {
        printf("Chave %d nao encontrada para remocao.\n", chave);
    }
}

int main () {
    arvore *A;
    // inicializa a árvore AVL, alocando memória para ela e setando a raiz como NULL
    assert(tree_build(&A));
    fprintf(stderr, "Árvore AVL construída com sucesso.\n");
    // cria alguns nodos para inserir na árvore AVL
    nodo *n1, *n2, *n3, *n4, *n5;
    assert(nodo_build(&n1, 10, NULL));
    assert(nodo_build(&n2, 20, NULL));
    assert(nodo_build(&n3, 30, NULL));
    assert(nodo_build(&n4, 40, NULL));
    assert(nodo_build(&n5, 50, NULL));

    fprintf(stderr, "Nodos construídos com sucesso.\n");

    // insere os nodos na árvore AVL, mantendo as propriedades da árvore AVL
    avl_insert(A, n1);
    avl_insert(A, n2);
    avl_insert(A, n3);
    avl_insert(A, n4);
    avl_insert(A, n5);

    fprintf(stderr, "Nodos inseridos na árvore AVL com sucesso.\n");

    fprintf(stderr, "Árvore AVL em ordem: ");
    inorder_tree_walk(A->raiz);
    fprintf(stderr, "\n");

    tree_free(A);

    fprintf(stderr, "Árvore AVL liberada com sucesso.\n");
    fprintf(stderr, "Teste finalizado com sucesso!\n\n");

    fprintf(stderr, "--- INICIO DO TESTE COMPLETO GEMINI---\n\n");

    assert(tree_build(&A));

    printf("--- TESTE DE INSERCAO E ROTACOES AVL ---\n");
    // Inserções estratégicas para forçar todos os tipos de rotação
    inserir_teste(A, 30);
    inserir_teste(A, 20);
    inserir_teste(A, 40);
    
    // Força Rotação à Direita (LL)
    inserir_teste(A, 10);
    inserir_teste(A, 5);  

    // Força Rotação à Esquerda (RR)
    inserir_teste(A, 50);
    inserir_teste(A, 60); 

    // Força Rotação Dupla Esquerda-Direita (LR)
    inserir_teste(A, 25);
    inserir_teste(A, 28); 

    // Força Rotação Dupla Direita-Esquerda (RL)
    inserir_teste(A, 45);
    inserir_teste(A, 42); 

    fprintf(stderr, "Pre-order (bom para ver a estrutura e raiz): \n");
    preorder_tree_walk(A->raiz);
    fprintf(stderr, "\n\n");

    fprintf(stderr, "In-order (obrigatoriamente ordenado crescente): \n");
    inorder_tree_walk(A->raiz);
    fprintf(stderr, "\n\n");

    printf("--- TESTE DE UTILITARIOS ---\n");
    nodo *min = tree_minimum(A->raiz);
    nodo *max = tree_maximum(A->raiz);
    printf("Minimo da arvore: %d | Maximo da arvore: %d\n", min->chave, max->chave);

    nodo *busca = tree_search(A->raiz, 25);
    if (busca) {
        nodo *suc = tree_successor(busca);
        if (suc) printf("O sucessor do %d eh o %d\n\n", busca->chave, suc->chave);
    }

    printf("--- TESTE DE REMOCAO AVL ---\n");
    // Caso 1: Remover um nó folha (sem filhos)
    remover_teste(A, 5);

    // Caso 2: Remover um nó com 1 filho
    // Ao remover o 10 (que agora só tem o 20 acima, precisamos ver a árvore).
    // O 10 tinha o 5 como filho esquerdo. Como tiramos o 5, ele ficou sem.
    // Vamos remover algo que sabidamente terá 1 filho ou testar folhas extras.
    remover_teste(A, 60);

    // Caso 3: Remover um nó interno com 2 filhos (vai acionar o sucessor/transplant)
    remover_teste(A, 30); // Geralmente é a raiz original ou um nó central importante

    fprintf(stderr, "\nIn-order apos remocoes (ainda deve estar ordenado): \n");
    inorder_tree_walk(A->raiz);
    fprintf(stderr, "\n");

    fprintf(stderr, "Pre-order apos remocoes (para conferir rebalanceamento): \n");
    preorder_tree_walk(A->raiz);
    fprintf(stderr, "\n\n");

    // Libera a memória para evitar memory leaks
    tree_free(A);
    printf("Arvore liberada. Teste finalizado com sucesso!\n");

    return 0;
}