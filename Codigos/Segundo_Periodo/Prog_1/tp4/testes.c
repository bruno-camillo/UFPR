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

    if (n == NULL)
        return 0;
        
    n -> chave = chave;
    n -> prox = lista -> ini;
    lista -> ini = n;

    return 1;
}

int main () {
    struct lista *l ;
    l = lista_cria();

    int chave = 5; 

    if (lista_insere_inicio(l, chave))
        printf("%d\n", l -> ini -> chave);
    else
        printf ("error\n");

    lista_destroi (&l);
    return 0;
}