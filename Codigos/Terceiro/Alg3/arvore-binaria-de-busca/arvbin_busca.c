#include <stdio.h>
#include <stdlib.h>
#include "arvbin_busca.h"

// retorna 1 se a árvore foi construída com sucesso, ou 0 se houve um erro
int tree_build (arvore **A) {
    if (!(*A = malloc(sizeof(arvore)))) {
        return 0; 
    }
    (*A)->raiz = NULL;
    (*A)->tam = 0;

    return 1; 
}

// retorna 1 se o nodo foi construído com sucesso, ou 0 se houve um erro
int nodo_build (nodo **n, int chave, void *conteudo) {
    if (!(*n = malloc(sizeof(nodo)))) {
        return 0; 
    }

    (*n)->chave = chave;
    (*n)->conteudo = conteudo;
    (*n)->pai = NULL;
    (*n)->esq = NULL;
    (*n)->dir = NULL;
    (*n)->altura = 0;

    return 1;
}

// retorna 1 se a árvore foi liberada com sucesso, ou 0 se houve um erro
int nodo_free (nodo *n) {
    if (n != NULL) {
        nodo_free(n->esq);
        nodo_free(n->dir);
        free(n);

        return 1;
    }
    return 0;
}

int tree_free (arvore *A) {
    if (A != NULL) {
        nodo_free(A->raiz);
        free(A);

        return 1;   
    }
    return 0;
}

void inorder_tree_walk (nodo * n) {
    if (n != NULL) {
        inorder_tree_walk(n->esq);
        fprintf(stderr, "%d ", n->chave);
        inorder_tree_walk(n->dir);
    }
}

void preorder_tree_walk (nodo * n) {
    if (n != NULL) {
        fprintf(stderr, "%d ", n->chave);
        preorder_tree_walk(n->esq);
        preorder_tree_walk(n->dir);
    }
}

void posorder_tree_walk (nodo * n) {
    if (n != NULL) {
        posorder_tree_walk(n->esq);
        posorder_tree_walk(n->dir);
        fprintf(stderr, "%d ", n->chave);
    }
}

nodo * tree_search (nodo * n, int chave) {
    // caso base: n é nulo ou n tem a chave buscada
    if (n == NULL || n->chave == chave) {
        return n;
    }
    // se a chave buscada é menor que a chave de n, busca na subárvore esquerda
    if (chave < n->chave) {
        return tree_search(n->esq, chave);
    } 
    // se a chave buscada é maior que a chave de n, busca na subárvore direita
    else {
        return tree_search(n->dir, chave);
    }
}

nodo * it_tree_search (nodo *n, int chave) {
    // busca iterativa: percorre a árvore a partir de n, seguindo os ponteiros para os filhos
    while (n != NULL && n->chave != chave) {
        // se a chave buscada é menor que a chave de n, segue para o filho esquerdo
        if (chave < n->chave) {
            n = n->esq;
        } 
        // se a chave buscada é maior que a chave de n, segue para o filho direito
        else {
            n = n->dir;
        }
    }
    return n;
}

nodo * tree_minimum (nodo *n) {
    while (n->esq != NULL) {
        n = n->esq;
    }
    return n;
}

nodo * tree_maximum (nodo *n) {
    while (n->dir != NULL) {
        n = n->dir;
    }
    return n;
}

nodo * tree_successor (nodo *n) {
    if (n->dir != NULL) {
        // se o nodo tem filho direito, o sucessor é o mínimo da subárvore direita
        return tree_minimum(n->dir); 
    }
    // se o nodo não tem filho direito, o sucessor é o primeiro ancestral 
    // para o qual n está na subárvore esquerda
    nodo *y = n->pai;
    while (y != NULL && n == y->dir) {
        n = y;
        y = y->pai;
    }
    return y;
}

// insere o nodo n na arvore A, mantendo as propriedades da árvore binária de busca
// retorna um ponteiro para o pai do nodo inserido, ou NULL se o nodo foi inserido como raiz 
nodo * tree_insert (arvore *A, nodo *n) {
    // verifica se os ponteiros para a árvore e para o nodo são nulos
    if (!A || !n) {
        return 0; 
    }

    nodo *y = NULL;
    nodo *x = A->raiz;
    while (x != NULL) {
        y = x;
        if (n->chave < x->chave) {
            x = x->esq;
        } else {
            x = x->dir;
        }
    }
    n->pai = y;
    if (y == NULL) {
        A->raiz = n; // a árvore estava vazia
    } else if (n->chave < y->chave) {
        y->esq = n;
    } else {
        y->dir = n;
    }

    A->tam++;

    return y;
}

// substitui a subárvore enraizada em u pela subárvore enraizada em v, atualizando os ponteiros dos pais
int transplant (arvore *A, nodo *u, nodo *v) {

    // se u é a raiz da árvore, atualiza a raiz para v
    if (u->pai == NULL) {
        A->raiz = v; 
    } 
    // u é filho esquerdo do pai
    else if (u == u->pai->esq) {
        u->pai->esq = v;
    } 
    // u é filho direito do pai
    else {
        u->pai->dir = v;
    }
    // se v não é nulo, atualiza o pai de v para ser o pai de u
    if (v != NULL) {
        v->pai = u->pai;
    }

    return 1;
}

// retorna 1 se o nodo foi removido com sucesso, ou 0 se houve um erro
int tree_delete (arvore *A, nodo *n) {
    if (!A || !n) {
        return 0; 
    }

    nodo *y; 
    // caso 1: n tem um filho à direita e nenhum filho à esquerda
    if (n->esq == NULL) {
        transplant(A, n, n->dir);
    } 
    // caso 2: n tem um filho à esquerda e nenhum filho à direita
    else if (n->dir == NULL) {
        transplant(A, n, n->esq);
    } 
    // caso 3: n tem dois filhos
    else {
        // sucessor de n
        y = tree_minimum(n->dir); 
        // se o sucessor não é o filho direito de n, substitui o sucessor por seu filho direito
        if (y != n->dir) {
            transplant(A, y, y->dir);
            y->dir = n->dir;
            y->dir->pai = y;
        }
        transplant(A, n, y);
        y->esq = n->esq;
        y->esq->pai = y;
    }

    free(n);
    A->tam--;

    return 1;
}