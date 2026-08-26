#include <stdio.h>
#include <stdlib.h>

// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  struct fpnodo_t *fim;		// último nodo da fila
  int num ;         // número de itens na fila
} ;

struct fprio_t *fprio_cria () {
  struct fprio_t *fila = malloc (sizeof (struct fprio_t));
  
  if (fila == NULL) 
    return NULL;
  
  fila -> prim = NULL;
  fila -> fim = NULL;
  fila -> num = 0;

  return fila;
}

struct fprio_t *fprio_destroi (struct fprio_t *f) {
	struct fpnodo_t *aux;

	if (!f)
		return NULL;

	/* percorre a fila até ela estar vazia */
    while (f -> prim != NULL) {
        /* auxiliar aponta para o primeiro elemento da fila,
         * e o começo da fila se desloca para o segundo elemento */
        aux = f -> prim;
        f -> prim = f -> prim -> prox;

		free (aux -> item);
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
int fprio_busca_repetido (struct fprio_t *f, void *item){
	struct fpnodo_t *aux;

	if (!f || !item)
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

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {
	struct fpnodo_t *n, *aux;

	if (!f || !item)
		return -1;
        
	// retorna erro se o item ja pertencer a fila
	if (fprio_busca_repetido(f, item))
			return -1;

	n = malloc (sizeof (struct fpnodo_t));
	if (n == NULL) 
		return -1;

	n -> item = item;
	n -> tipo = tipo;
	n -> prio = prio;

	//verifica se a fila está vazia
	if (f -> prim == NULL) {
		n -> prox = NULL;
		f -> prim = n;
		f -> fim = n;
	}
	//verifica se o novo nó deve ser inserido no início da fila
	//alem disso, se a fila tiver apenas um elemento e a prioridade do novo nó for igual ou maior
	//que a do primeiro, ele deve ser inserido antes deste
	else if (f -> prim -> prio > prio || (f -> num == 1 && f -> prim -> prio > prio)) {
			n -> prox = f -> prim;
			f -> prim = n;
	} 
	//verifica se a fila tem apenas um elemento e a prioridade do novo nó for menor
	else if (f -> num == 1 && f -> prim -> prio <= prio) {
			n -> prox = NULL;
			f -> prim -> prox = n; 
			f -> fim = n;
	} 
	//busca a posicao correta para o novo nó
	else {			
		aux = f -> prim;
		while (aux -> prox -> prox != NULL && aux -> prox -> prio <= prio) {
			aux = aux -> prox;
		}

		//verifica se o novo nó deve ser inserido no final da fila
		if (aux -> prox -> prox == NULL && aux -> prox -> prio <= prio) {
			n -> prox = NULL;
			aux -> prox -> prox = n;
			f -> fim = n;
		}
		//insere o novo nó na posição correta
		else if (aux -> prox -> prio > prio) {
			n -> prox = aux -> prox;
			aux -> prox = n;
		} 
		else {
			n -> prox = aux -> prox -> prox;
			aux -> prox -> prox = n;
		}
	}

	return f -> num++;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio) {
	struct fpnodo_t *aux;
	void *item;

	if (!f || !tipo || !prio)
		return NULL;

	//verifica fila vazia
	if (f -> prim == NULL) 
		return NULL;
	
	aux = f -> prim;

	f -> prim = aux -> prox;
	f -> num--;

	*tipo = aux -> tipo;
	*prio = aux -> prio;
	item = aux -> item;

	free (aux);

	return item;
}

int fprio_tamanho (struct fprio_t *f) {
	if (!f) 
		return -1;
	
	return f -> num;
}

void fprio_imprime (struct fprio_t *f) {
	struct fpnodo_t *aux;

	if (!f)
		return;

	aux = f -> prim;
	while (aux -> prox != NULL) {
		printf("(%d %d) ", aux -> tipo, aux -> prio);
		aux =  aux -> prox;
	}
	printf("(%d %d) ", aux -> tipo, aux -> prio);
}

int main () {
    struct fprio_t *f;
    void *item;
    int *p;
    int tipo = 1; 
    int prio;

    f = fprio_cria();

    for (int i = 0; i <= 10; i++) {
        p = malloc (sizeof(int));
        (*p) = i;
        item = p;
        if (i % 2 == 0)
            prio = 0;
        else    
            prio = 1;
        printf ("INSERINDO O ITEM %d de tipo %d e prioridade %d\n", i, tipo, prio);
        fprio_insere (f, item, tipo, prio);
        printf ("FILA: ");
        fprio_imprime(f);

        printf (" (%d itens)\n", f -> num);
        printf("\n");
    }

    return 0;
}