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

/*
  Retorna 1 se a lista está vazia e 0 caso contrário.
*/
int lista_vazia (struct lista *lista) {
    if (lista -> ini == NULL)
        return 1;
    return 0;
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

    if (n == NULL)
        return 0;

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

    /*testa se a lista ta vazia*/
    if (lista_vazia(lista)) {
        lista_insere_inicio(lista, chave);

        free (n);
        n = NULL;

        return 1;
    }

    n -> chave = chave;

    /* percorre toda a lista se a nova chave for maior que a chave do primeiro elemento
     * caso contrario, a nova chave eh inserida no começo */
    if (lista -> ini -> chave < n -> chave) {
        while ((aux -> prox != NULL) && (aux -> prox -> chave < n -> chave))
            aux = aux -> prox;
        /*insere o novo nodo na lista*/
        n -> prox = aux -> prox;
        aux -> prox = n;
    } else {
        n -> prox = lista -> ini;
        lista -> ini = n;
    }

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
    (*chave) = aux -> chave; /*variavel chave recebe o valor da chave do nodo a ser removido*/

    free (aux);

    lista -> tamanho--;

    return 1;
}

/*
 * Remove o elemento do final da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_fim (struct lista *lista, int *chave){
    struct nodo *aux = lista -> ini;

    if (lista_vazia(lista))
        return 0;

    while (aux -> prox != NULL)
        aux = aux -> prox;
    
    (*chave) = aux -> chave; /* chave recebe o valor da chave do nodo a ser removido */

    free (aux -> prox);
    aux -> prox = NULL;

    lista -> tamanho--;

    return 1;
}

/*
 * Remove o elemento chave da lista mantendo-a ordenada.
 * A função considera que a cheve esta presente na lista, quem chama
 * esta funcao deve garantir isso.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_ordenado (struct lista *lista, int chave){
    struct nodo *aux = lista -> ini;
    struct nodo *aux2;

    if (lista_vazia(lista))
        return 0;

    while ((aux -> prox != NULL) && (aux -> prox -> chave != chave))
        aux = aux -> prox;

    aux2 = aux -> prox;
    aux -> prox = aux2 -> prox;

    lista -> tamanho--;

    free (aux2);

    return 1;
}

int main () {
    struct lista *l;
  
    l = lista_cria();
    int chave, i; 
    struct nodo *aux;

    scanf ("%d", &chave);
    while (chave != 0) {
        lista_insere_ordenado (l, chave);
        scanf ("%d", &chave);
    }

    aux = l -> ini;

    for (i = 1; i <= l -> tamanho; i++) {
        printf ("%d ", aux -> chave);
        aux = aux -> prox;
    }
    printf("\n");
    
    lista_remove_ordenado(l, 5);

    aux = l -> ini;

    for (i = 1; i <= l -> tamanho; i++) {
        printf ("%d ", aux -> chave);
        aux = aux -> prox;
    }
    printf("\n");

    lista_destroi (&l);

    return 0;
}