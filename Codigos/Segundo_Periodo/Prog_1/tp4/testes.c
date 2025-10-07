#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};

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
        aux = (*lista) -> ini;
        (*lista) -> ini = (*lista) -> ini -> prox;

        free (aux);

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

    if (n == NULL)
        return 0;
        
    n -> chave = chave;
    n -> prox = lista -> ini;
    lista -> ini = n;

    lista -> tamanho++;

    return 1;
}

/*
 * Insere chave no final da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
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

/*
 * Insere chave em ordem na lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
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
  Retorna 1 se a lista está vazia e 0 caso contrário.
*/
int lista_vazia (struct lista *lista) {
    if (lista -> ini == NULL)
        return 1;
    return 0;
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
    free (aux);

    return 1;
}

int main () {
    struct lista *l ;
    l = lista_cria();

    int chave = 1; 

    if (lista_insere_inicio(l, chave))
        printf("%d\n", l -> ini -> chave);
    else
        printf ("error\n");

    if (lista_insere_fim(l, 7))
        printf("%d\n", l -> ini -> prox -> chave);
    else
        printf ("error\n");

    if (lista_insere_ordenado(l, 9))
        printf("%d\n", l -> ini -> prox -> prox -> chave);
    else
        printf ("error\n");

    lista_destroi (&l);
    return 0;
}