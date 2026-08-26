#ifndef ARVORE_AVL
#define ARVORE_AVL

#include "arvbin_busca.h"

// funções para manipular a árvore AVL

// insere o nodo n na árvore A, mantendo as propriedades da árvore AVL
void avl_insert (arvore *A, nodo *n);

// faz uma rotação à esquerda no nodo n e retorna o novo nodo raiz da subárvore
nodo * rotate_left (nodo *n);

// faz uma rotação à direita no nodo n e retorna o novo nodo raiz da subárvore
nodo * rotate_right (nodo *n);

// faz uma rotação à esquerda no filho esquerdo de n e depois uma rotação à direita em n, retornando o novo nodo raiz da subárvore
nodo * rotate_left_right (nodo *n);

// faz uma rotação à direita no filho direito de n e depois uma rotação à esquerda em n, retornando o novo nodo raiz da subárvore
nodo * rotate_right_left (nodo *n);

// balanceia a subárvore enraizada em n, retornando o novo nodo raiz da subárvore
nodo * avl_balance (nodo *n);

// remove o nodo n da árvore A, mantendo as propriedades da árvore AVL
void avl_delete (arvore *A, nodo *n);

#endif