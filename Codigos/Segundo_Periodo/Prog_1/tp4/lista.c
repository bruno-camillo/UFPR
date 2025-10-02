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

/*
 * Cria e retorna uma nova lista.
 * Retorna NULL em caso de erro de alocação.
*/
struct lista * lista_cria () {
    struct lista *l = malloc (sizeof(struct lista));

    l -> ini = NULL;
    l -> ptr = NULL;
    l -> tamanho = 0;

    if (l == NULL)
        return NULL;
    return l; 
}

/* Desaloca toda memoria da lista e faz lista receber NULL. */
void lista_destroi (struct lista **lista){
    struct nodo *aux;
    while ((*lista) -> ini != NULL) {
        aux -> prox = (*lista) -> ini;
        (*lista) -> ini = (*lista) -> ini -> prox;

        free (aux);
        aux = NULL;

        (*lista) -> tamanho--;
    }

    free ((*lista));
    lista = NULL;
}

/*
 * Insere chave no inicio da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *n = malloc (sizeof(struct nodo));

    if (!(n = NULL))
        return 0;
        
    n -> chave = chave;
    n -> prox = lista -> ini;
    lista -> ini = n;

    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
}

int lista_insere_ordenado (struct lista *lista, int chave){
}

int lista_remove_inicio (struct lista *lista, int *chave){
}

int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista){
}

int lista_tamanho (struct lista *lista){
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
}
