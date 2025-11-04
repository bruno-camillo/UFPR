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

     /*inicializacao dos ponteiros*/
    l -> ini = NULL;   
    l -> ptr = NULL;    
    l -> tamanho = 0;   

    if (l == NULL)
        return NULL;
    return l; 
}

int lista_vazia (struct lista *lista) {
    if (lista -> ini == NULL)
        return 1;
    return 0;
}

int lista_tamanho (struct lista *lista) {
    return lista -> tamanho;
}

int lista_pertence (struct lista *lista, int chave) {
    struct nodo *aux = lista -> ini;

    /* percorre o vetor até o ultimo nodo, ou até encontrar o elemento chave */
    while ((aux -> prox != NULL) && (aux -> chave != chave))
        aux = aux -> prox;

    if (aux -> chave == chave)
        return 1;

    return 0;
}

/* Desaloca toda memoria da lista e faz lista receber NULL. */
void lista_destroi (struct lista **lista){
    struct nodo *aux;

    /* percorre a lista até ela estar vazia */
    while ((*lista) -> ini != NULL) {
        /* auxiliar aponta para o primeiro elemento da lista,
         * e o começo da lista se desloca para o segundo elemento */
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

    /* inicialização do novo nodo */
    n -> chave = chave;
    n -> prox = lista -> ini;
    lista -> ini = n;

    lista -> tamanho++;

    return 1;
}

/* OBS: condição vem antes das variaveis locais para não precisar alocar memória
     * e depois precisar libera-la com a chamada da função insere_inicio */
int lista_insere_fim (struct lista *lista, int chave){
    /* testa se a lista esta vazia, caso positivo, insere o elemento no inicio */
    if (lista_vazia(lista)) {
        lista_insere_inicio(lista, chave);

        return 1;
    }

    struct nodo *aux = lista -> ini;
    struct nodo *n = malloc (sizeof(struct nodo));

    if (n == NULL)
        return 0;

    /* inicialização do novo nodo */
    n -> chave = chave;
    n -> prox = NULL;

    /* percorre a lista até o ultimo nodo */
    while (aux -> prox != NULL)
        aux = aux -> prox;

    aux -> prox = n; 

    lista -> tamanho++;

    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave) {
    /*testa se a lista ta vazia*/
    if (lista_vazia(lista)) {
        lista_insere_inicio(lista, chave);

        return 1;
    }

    struct nodo *n = malloc(sizeof(struct nodo));
    struct nodo *aux = lista -> ini;

    if (n == NULL)
        return 0;

    n -> chave = chave;

    /* percorre toda a lista se a nova chave for maior que a chave do primeiro elemento
     * caso contrario, a nova chave eh inserida no começo */
    if (lista -> ini -> chave < n -> chave) {
        while ((aux -> prox != NULL) && (aux -> prox -> chave < n -> chave))
            aux = aux -> prox;

        /* insere o novo nodo na lista */
        n -> prox = aux -> prox;
        aux -> prox = n;

    } else {
        n -> prox = lista -> ini;
        lista -> ini = n;
    }

    lista -> tamanho++;

    return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave) {
    if (lista_vazia(lista))
        return 0;

    struct nodo *aux = lista -> ini;

    lista -> ini = aux -> prox;
    /* variavel chave recebe o valor da chave do nodo que sera removido */
    (*chave) = aux -> chave; 

    free (aux);

    lista -> tamanho--;

    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    struct nodo *aux = lista -> ini;

    if (lista_vazia(lista))
        return 0;

    /* verifica se a lista possui apenas um elemento */
    if (lista -> tamanho == 1) {
        lista_remove_inicio (lista, chave);

        return 1;
    }

    /* percorre a lista até o penultimo nodo */
    while (aux -> prox -> prox != NULL)
        aux = aux -> prox;
    
    (*chave) = aux -> chave; 
    
    /* libera o ultimo nodo e aponta o penultimo para NULL*/
    free (aux -> prox);
    aux -> prox = NULL;

    lista -> tamanho--;

    return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave){
    struct nodo *aux = lista -> ini;
    struct nodo *aux2;

    if (lista_vazia(lista))
        return 0;

    /* percorre a lista até encontrar o elemento chave
     * caso o elemento chave nao seja o primeiro da lista */
    if (lista -> ini -> chave != chave) {
        while (aux -> prox -> chave != chave)
            aux = aux -> prox; 
    } else { 
        /* caso o elemento chave seja o primeiro da lista */
        lista -> ini = aux -> prox;
        free (aux);

        lista -> tamanho--;   
        
        return 1;
    }

    /* remove o nodo que contem a chave */
    aux2 = aux -> prox;
    aux -> prox = aux -> prox -> prox;

    lista -> tamanho--;

    free (aux2);

    return 1;
}

void lista_inicia_iterador (struct lista *lista) {
    lista -> ptr = lista -> ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave) {
    if (lista -> ptr == NULL)
        return 0;
    
    /* atribui a chave do nodo apontado pelo iterador 
     * e depois aponta para o proximo */
    (*chave) = lista -> ptr -> chave;
    lista -> ptr = lista -> ptr -> prox;
    
    return 1;
}