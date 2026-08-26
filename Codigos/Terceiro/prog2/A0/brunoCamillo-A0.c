#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct porcao {
    int tipo;
    // numero de unidades da porcao
    int n;
} porcao;

struct nodo {
    struct nodo *prox;
    porcao prato;
};

typedef struct lista {
    struct nodo *ini;
    struct nodo *fim;
    int tam;
}lista;

// cria e retorna uma nova lista
// retorna NULL em caso de erro de alocaçao
lista * lista_cria () {
    lista *l = malloc (sizeof(struct lista));
    if (l == NULL)
        return NULL;

    /*inicializacao dos ponteiros*/
    l -> ini = NULL;   
    l -> fim = NULL;    
    l -> tam = 0;

    
    return l; 
}

// verifica se a lista esta vazia
// retorna true caso esteja, e false caso contrario
bool lista_vazia(lista* l) {
    if (l -> tam == 0)
        return true;
    return false;
}

// insere um elemento no fim da lista
// retorna 1 em caso de sucesso e 0 caso contrario
int lista_insere(lista *l, porcao *p) {
    struct nodo *novo_p = malloc(sizeof(struct nodo));

    if (!l || !p || !novo_p)
        return 0; 

    if (l -> tam == 0)
            l -> ini = novo_p;

    novo_p -> prato = *p;
    novo_p -> prox = l -> ini;
    if (l -> fim != NULL)
        l -> fim -> prox = novo_p;
    l -> fim = novo_p;

    l -> tam++;

    return 1;
}

// remove o primeiro elemento da lista
// retorna 1 em caso de sucesso e 0 caso contrario
int lista_remove(lista *l) {
    if (!l)
        return 0;

    struct nodo *aux = l -> ini;

    l -> ini = aux -> prox;
    l -> fim -> prox = l -> ini;

    l -> tam--;

    free (aux);

    return 1;
}

// insere um novo prato escolhido pelo usuario na lista
// retorna 1 em caso de sucesso e 0 caso contrario
int cadrastro (lista *l, porcao * p) {
    if (!l)
        return 0;
    int i;

    printf("Qual tipo de prato deseja cadrastrar?\n");
    scanf("%d", &i);

    p -> tipo = i;
    p -> n = 5;

    lista_insere(l, p);

    return 1;
}

int inicializa_porcoes(lista * l) {
    porcao * p;
    int i = 1;

    while (i != 0) {
        p = malloc(sizeof(porcao));

        cadrastro(l, p);

        printf("Caso deseje parar o cadastro dos pratos, digite 0!\nCaso contrario, digite 1!\n");

        scanf("%d", &i);

        free(p);
    }
}

void cliente_retira (struct nodo * n) {
    if (!n)
        return;

    n -> prato.n = n -> prato.n - (rand() % 3); 

    return;
}

void rodizio (lista *l) {
    if (!l)
        return;

    struct nodo *aux = l -> ini;
    for (int i = 1; i <= l -> tam; i++) {
        cliente_retira(aux);
        if (aux -> prato.n <= 0)
            lista_remove(l);
        aux = aux -> prox;
    }

    // faz a rotação da esteira
    l -> ini = l -> ini -> prox;
    l -> fim = l -> fim -> prox;

    return;
}

void lista_imprime (lista *l) {
    struct nodo *aux = l -> ini;
    
    if (lista_vazia(l)) 
        printf("lista vazia\n");
    else { 
        while(aux -> prox != l -> ini) {
            printf("Prato do tipo %d com %d unidades\n", aux -> prato.tipo, aux -> prato.n);
            aux = aux -> prox;
        }            
        printf("Prato do tipo %d com %d unidades\n", l -> fim->prato.tipo, l -> fim -> prato.n);
    }

    return;
}

int main () {
    lista * restaurante = lista_cria();
    int i;

    printf("Inicialize as porcoes\n");
    inicializa_porcoes(restaurante);

    lista_imprime(restaurante);

    printf("Digite 1 para iniciar o rodizio, digite 0 para para-lo\n");
    scanf("%d", &i);

    while (!lista_vazia(restaurante) && i != 0) {
        rodizio(restaurante);
        lista_imprime(restaurante);
        printf("O rodizio foi realizado com sucesso!\nDeseja continuar?\n");
        scanf("%d", &i);
    }

    if (lista_vazia(restaurante))
        printf("O rodizio acabou, volte mais tarde!\n");

    return 1;
}