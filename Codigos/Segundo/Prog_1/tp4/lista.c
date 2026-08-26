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
<<<<<<< HEAD

/*
 * Cria e retorna uma nova lista.
 * Retorna NULL em caso de erro de alocação.
*/
struct lista * lista_cria () {
    struct lista *l = malloc (sizeof(struct lista));

    l -> ini = NULL;
    l -> ptr = NULL;
    l -> tamanho = 0;
=======
struct lista * lista_cria () {
    struct lista *l = malloc (sizeof(struct lista));

     /*inicializacao dos ponteiros*/
    l -> ini = NULL;   
    l -> ptr = NULL;    
    l -> tamanho = 0;   
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c

    if (l == NULL)
        return NULL;
    return l; 
}

<<<<<<< HEAD
/*
  Retorna 1 se a lista está vazia e 0 caso contrário.
*/
=======
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
int lista_vazia (struct lista *lista) {
    if (lista -> ini == NULL)
        return 1;
    return 0;
}

<<<<<<< HEAD
/*
  Retorna o numero de elementos da lista
*/
=======
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
int lista_tamanho (struct lista *lista) {
    return lista -> tamanho;
}

<<<<<<< HEAD
/*
  Retorna 1 se o elemento chave esta presente na lista,
  caso contrário retorna 0.
*/
int lista_pertence (struct lista *lista, int chave) {
    struct nodo *aux = lista -> ini;

=======
int lista_pertence (struct lista *lista, int chave) {
    struct nodo *aux = lista -> ini;

    /* percorre o vetor até o ultimo nodo, ou até encontrar o elemento chave */
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
    while ((aux -> prox != NULL) && (aux -> chave != chave))
        aux = aux -> prox;

    if (aux -> chave == chave)
        return 1;

    return 0;
}

/* Desaloca toda memoria da lista e faz lista receber NULL. */
void lista_destroi (struct lista **lista){
    struct nodo *aux;

<<<<<<< HEAD
    while ((*lista) -> ini != NULL) {
=======
    /* percorre a lista até ela estar vazia */
    while ((*lista) -> ini != NULL) {
        /* auxiliar aponta para o primeiro elemento da lista,
         * e o começo da lista se desloca para o segundo elemento */
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
        aux = (*lista) -> ini;
        (*lista) -> ini = (*lista) -> ini -> prox;

        free (aux);

        (*lista) -> tamanho--;
    }

    free ((*lista));
    lista = NULL;
}

<<<<<<< HEAD
/*
 * Insere chave no inicio da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
=======
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *n = malloc (sizeof(struct nodo));

    if (n == NULL)
        return 0;
<<<<<<< HEAD
        
=======

    /* inicialização do novo nodo */
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
    n -> chave = chave;
    n -> prox = lista -> ini;
    lista -> ini = n;

    lista -> tamanho++;

    return 1;
}

<<<<<<< HEAD
/*
 * Insere chave no final da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *n = malloc (sizeof(struct nodo));
    struct nodo *aux = lista -> ini;
=======
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
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c

    if (n == NULL)
        return 0;

<<<<<<< HEAD
    /*testa se a lista ta vazia*/
    if (lista_vazia(lista)) {
        lista_insere_inicio(lista, chave);

        free (n);
        n = NULL;
        
        return 1;
    }

    n -> chave = chave;
    n -> prox = NULL;

    while (aux -> prox != NULL)
        aux = aux -> prox;

    aux -> prox = n;
=======
    /* inicialização do novo nodo */
    n -> chave = chave;
    n -> prox = NULL;

    /* percorre a lista até o ultimo nodo */
    while (aux -> prox != NULL)
        aux = aux -> prox;

    aux -> prox = n; 
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c

    lista -> tamanho++;

    return 1;
}

<<<<<<< HEAD
/*
 * Insere chave em ordem na lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_ordenado (struct lista *lista, int chave) {
=======
int lista_insere_ordenado (struct lista *lista, int chave) {
    /*testa se a lista ta vazia*/
    if (lista_vazia(lista)) {
        lista_insere_inicio(lista, chave);

        return 1;
    }

>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
    struct nodo *n = malloc(sizeof(struct nodo));
    struct nodo *aux = lista -> ini;

    if (n == NULL)
        return 0;

<<<<<<< HEAD
    /*testa se a lista ta vazia*/
    if (lista_vazia(lista)) {
        lista_insere_inicio(lista, chave);

        free (n);
        n = NULL;

        return 1;
    }

=======
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
    n -> chave = chave;

    /* percorre toda a lista se a nova chave for maior que a chave do primeiro elemento
     * caso contrario, a nova chave eh inserida no começo */
    if (lista -> ini -> chave < n -> chave) {
        while ((aux -> prox != NULL) && (aux -> prox -> chave < n -> chave))
            aux = aux -> prox;
<<<<<<< HEAD
        /*insere o novo nodo na lista*/
        n -> prox = aux -> prox;
        aux -> prox = n;
=======

        /* insere o novo nodo na lista */
        n -> prox = aux -> prox;
        aux -> prox = n;

>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
    } else {
        n -> prox = lista -> ini;
        lista -> ini = n;
    }

    lista -> tamanho++;

    return 1;
}

<<<<<<< HEAD
/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
=======
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
int lista_remove_inicio (struct lista *lista, int *chave) {
    if (lista_vazia(lista))
        return 0;

    struct nodo *aux = lista -> ini;

    lista -> ini = aux -> prox;
<<<<<<< HEAD
    (*chave) = aux -> chave; /*variavel chave recebe o valor da chave do nodo a ser removido*/
=======
    /* variavel chave recebe o valor da chave do nodo que sera removido */
    (*chave) = aux -> chave; 
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c

    free (aux);

    lista -> tamanho--;

    return 1;
}

<<<<<<< HEAD
/*
 * Remove o elemento do final da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
=======
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
int lista_remove_fim (struct lista *lista, int *chave){
    struct nodo *aux = lista -> ini;

    if (lista_vazia(lista))
        return 0;

    /* verifica se a lista possui apenas um elemento */
    if (lista -> tamanho == 1) {
<<<<<<< HEAD
        (*chave) = aux -> chave;

        free (aux);
        lista -> ini = NULL;
=======
        lista_remove_inicio (lista, chave);
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c

        return 1;
    }

<<<<<<< HEAD
    while (aux -> prox -> prox != NULL)
        aux = aux -> prox;
    
    (*chave) = aux -> chave; /* chave recebe o valor da chave do nodo a ser removido */
    
=======
    /* percorre a lista até o penultimo nodo */
    while (aux -> prox -> prox != NULL)
        aux = aux -> prox;
    
    (*chave) = aux -> chave; 
    
    /* libera o ultimo nodo e aponta o penultimo para NULL*/
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
    free (aux -> prox);
    aux -> prox = NULL;

    lista -> tamanho--;

    return 1;
}

<<<<<<< HEAD
/*
 * Remove o elemento chave da lista mantendo-a ordenada.
 * A função considera que a cheve esta presente na lista, quem chama
 * esta funcao deve garantir isso.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
=======
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
int lista_remove_ordenado (struct lista *lista, int chave){
    struct nodo *aux = lista -> ini;
    struct nodo *aux2;

<<<<<<< HEAD
    if ((lista_vazia(lista)) || !(lista_pertence(lista, chave)))
        return 0;

    while ((aux -> prox != NULL) && (aux -> prox -> chave != chave))
        aux = aux -> prox;

    aux2 = aux -> prox;
    aux -> prox = aux2 -> prox;
=======
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
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c

    lista -> tamanho--;

    free (aux2);

    return 1;
}

<<<<<<< HEAD
/*
 * Inicializa ptr usado na funcao incrementa_iterador.
 * A funcao main deve garantir que a lista nao eh vazia.
*/
=======
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
void lista_inicia_iterador (struct lista *lista) {
    lista -> ptr = lista -> ini;
}

<<<<<<< HEAD
/*
 * Devolve no parametro *chave o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro da lista).
*/
int lista_incrementa_iterador (struct lista *lista, int *chave) {
    (*chave) = lista -> ptr -> chave;

    if (lista -> ptr -> prox == NULL)
        return 0;

    lista -> ptr = lista -> ptr -> prox;

=======
int lista_incrementa_iterador (struct lista *lista, int *chave) {
    if (lista -> ptr == NULL)
        return 0;
    
    /* atribui a chave do nodo apontado pelo iterador 
     * e depois aponta para o proximo */
    (*chave) = lista -> ptr -> chave;
    lista -> ptr = lista -> ptr -> prox;
    
>>>>>>> ccaaa3c8dbfee2407cd599582fffe1549f0eba1c
    return 1;
}