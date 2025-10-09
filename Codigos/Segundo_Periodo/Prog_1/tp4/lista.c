#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista * lista_cria () {
    struct lista *l = malloc (sizeof(struct lista));

    l -> ini = NULL;
    l -> ptr = NULL;
    l -> tamanho = 0;

    if (l == NULL)
        return NULL;
    return l; 
}

void lista_destroi (struct lista **lista){
    struct nodo *aux;

    while ((*lista) -> ini != NULL) {
        aux = (*lista) -> ini;
        (*lista) -> ini = (*lista) -> ini -> prox;

        free (aux);

        (*lista) -> tamanho--;
    }

    free ((*lista));
    lista = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *n = malloc (sizeof(struct nodo));

    if (n == NULL)
        return 0;
        
    n -> chave = chave;
    n -> prox = lista -> ini;
    lista -> ini = n;

    lista -> tamanho++;

    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *n = malloc (sizeof(struct nodo));
    struct nodo *aux = lista -> ini;
    int i;

    if (n == NULL)
        return 0;

    n -> chave = chave;
    n -> prox = NULL;

    for (i = 1; i < lista -> tamanho; i++)
        aux = aux -> prox; 

    aux -> prox = n;
    lista -> tamanho++;

    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave) {
    struct nodo *n = malloc(sizeof(struct nodo));
    struct nodo *aux = lista -> ini;

    if (n == NULL)
        return 0;

    n -> chave = chave;

    /* passa pelo vetor para encontrar a posicao certa do novo nodo,
     * se a chave do nodo n for monor que a chave do primeiro nodo da lista 
     * E se o aux nao apontar para o ultimo elemento */
    if (lista -> ini -> chave < n -> chave)
        while ((aux -> prox != NULL) && (aux -> prox -> chave < n -> chave))
            aux = aux -> prox;

    /*insere o novo nodo na lista*/
    n -> prox = aux -> prox;
    aux -> prox = n;

    lista -> tamanho++;

    return 1;
}

/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_inicio (struct lista *lista, int *chave) {
    if ( lista_vazia(lista) )
        return 0;

    struct nodo *aux = lista -> ini;

    lista -> ini = aux -> prox;
    (*chave) = aux -> chave; //variavel chave recebe o valor do nodo a ser removido

    free (aux);

    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista) {
    if (lista -> ini == NULL)
        return 1;
    return 0;
}
int lista_tamanho (struct lista *lista){
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
}
