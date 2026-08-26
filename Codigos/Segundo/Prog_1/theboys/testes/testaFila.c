#include <stdio.h>
#include <stdlib.h>

// descreve um nodo da fila 
struct fila_nodo_t
{
	int item;					// item associado ao nodo
	struct fila_nodo_t *prox;	// próximo nodo
};

// descreve uma fila 
struct fila_t
{
	struct fila_nodo_t *prim ;	// primeiro nodo da fila
	struct fila_nodo_t *ult ;	// último nodo da fila
	int num ;					// número de itens na fila
};

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria () {
	struct fila_t *f = malloc (sizeof (struct fila_t));

	if (!f)
		return NULL;
	
	f -> prim = NULL;
	f -> ult = NULL;
	f -> num = 0;

	return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f) {
	struct fila_nodo_t *aux;

	if (!f)
		return NULL;

	while (f -> prim != NULL) {
        aux = f -> prim;
        f -> prim = f -> prim -> prox;

        free (aux);

        f -> num--;
    }

    free (f);
    f = NULL;

    return NULL;
}

// Busca um item repetido na fila
// Retorna 1 caso encontre, 0 caso contrario
// Retorna -1 em caso de erro
int fila_busca_repetido (struct fila_t *f, int item){
	struct fila_nodo_t *aux;

	if (!f)
		return -1;

	aux = f -> prim;

	// percorre a fila ate encontrar o elemento ou chegar ou final
	while (aux != NULL) {
		if (aux -> item == item) 
			return 1;
		aux = aux -> prox;
	}

	return 0;
}

// Insere um item no final da fila (politica FIFO).
// Retorno: 1 se tiver sucesso ou 0 se falhar.
int fila_insere (struct fila_t *f, int item) {
    struct fila_nodo_t *n;

    if (!f)
        return -1;

    // retorna erro caso o item ja pertença a fila
    if (fila_busca_repetido (f, item)) {
        return -1; }

    n = malloc (sizeof(struct fila_nodo_t));

    if (!n)
        return -1;

    n -> item = item;
    n -> prox = NULL;

    if (f -> prim == NULL) 
        f -> prim = n;
    else
        f -> ult -> prox = n;

    f -> ult = n;
    
    return f -> num++;
}

// Retira o primeiro item da fila e o devolve
// Retorno 1 se a operação foi bem sucedida e 0 caso contrário
int fila_retira (struct fila_t *f, int *item) {
    struct fila_nodo_t *aux;

    // verifica se o parametro existe
    if (!f || !item)
        return 0;

    // verifica se a fila eh vazia
    if (f -> prim == NULL)
        return 0;

    aux = f -> prim;

    
    if (f -> num != 1)
        f -> prim = aux -> prox;
    else
    {    
        f -> prim = NULL;
        f -> ult = NULL;
    }

    f -> num--;

    (*item) = aux -> item;

    free (aux);

    return 1;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f) {
    if (!f)
        return -1;

    return f -> num;
}

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f) {
    struct fila_nodo_t *aux;

    if (!f)
        return;

    if (f -> prim == NULL) {
        printf("FILA VAZIA");
        return;
    }

    aux = f -> prim;
    while (aux -> prox != NULL) {
        printf("%d ", aux -> item);
        aux = aux -> prox;
    }
    printf("%d", aux -> item);
}

int main () {
    struct fila_t *f;
    f = fila_cria();

    for (int i = 0; i <= 10; i++) {
        
        printf ("INSERINDO O ITEM: %d\n", i);
        fila_insere (f, i);
        printf ("FILA: ");
        fila_imprime(f);
        printf (" (%d itens)\n", f -> num);
        printf("\n");
    }

    for (int i = 0; i <= 10; i++) {
        
        printf ("REMOVENDO O ITEM: %d\n", i);
        fila_retira (f, &i);
        printf ("FILA: ");
        fila_imprime(f);
        printf (" (%d itens)\n", f -> num);
        printf("\n");
    }

    for (int i = 20; i <= 30; i++) {
        
        printf ("INSERINDO O ITEM: %d\n", i);
        fila_insere (f, i);
        printf ("FILA: ");
        fila_imprime(f);
        printf (" (%d itens)\n", f -> num);
        printf("\n");
    }
    fila_destroi (f);
    
    return 0;
}