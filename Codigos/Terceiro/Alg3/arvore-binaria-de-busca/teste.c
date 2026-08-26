#include <stdio.h>
#include <stdlib.h>
#include "arvbin_busca.h"

int main() {
    arvore *A;
    nodo *n1, *n2, *n3, *n4, *n5;

    // teste das funções da árvore binária de busca
    if (tree_build(&A)) {
        printf("Sucesso ao construir a árvore.\n");
    } else {
        printf("Erro ao construir a árvore.\n");
        return 1;
    }
    
    if (nodo_build(&n1, 5, NULL)) {
        printf("Sucesso ao construir o nodo n1.\n");
    } else {
        printf("Erro ao construir o nodo n1.\n");
        return 1;
    }

    // construção dos nodos n2, n3, n4 e n5
    nodo_build(&n2, 3, NULL);
    nodo_build(&n3, 7, NULL);
    nodo_build(&n4, 2, NULL);
    nodo_build(&n5, 4, NULL);

    fprintf(stderr, "Árvore construída com sucesso.\n");
    
    // inserção dos nodos na árvore
    tree_insert(A, n1);
    tree_insert(A, n2);
    tree_insert(A, n3);
    tree_insert(A, n4);
    tree_insert(A, n5);

    fprintf(stderr, "Nodos inseridos com sucesso.\n");

    fprintf(stderr, "Inorder: ");
    inorder_tree_walk(A->raiz);

    fprintf(stderr, "\nÁrvore impressa em ordem.\n");

    fprintf(stderr, "\nPreorder: ");
    preorder_tree_walk(A->raiz);

    fprintf(stderr, "\nPosorder: ");
    posorder_tree_walk(A->raiz);

    fprintf(stderr, "\nSearch for 3: %d\n", tree_search(A->raiz, 3)->chave);

    fprintf(stderr, "Iterative search for 4: %d\n", it_tree_search(A->raiz, 4)->chave);

    fprintf(stderr, "Minimum: %d\n", tree_minimum(A->raiz)->chave);

    fprintf(stderr, "Maximum: %d\n", tree_maximum(A->raiz)->chave);

    fprintf(stderr, "Successor of 3: %d\n", tree_successor(tree_search(A->raiz, 3))->chave);

    // teste de remoção de um nodo
    tree_delete(A, tree_search(A->raiz, 3));
    fprintf(stderr, "\nNodo removido com sucesso.\n");

    inorder_tree_walk(A->raiz);
    fprintf(stderr, "\nÁrvore impressa em inorder após remoção.\n");

    tree_free(A);  


    return 0;
}