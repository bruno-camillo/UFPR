#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipo_deque.h"

void inicializar_deque(deque* d) {
    d->inicio = NULL;
    d->fim = NULL;
    d->tamanho = 0;
}

void inicializar_nodo_inicio(nodo_deque* nodo, int valor, nodo_deque* prox) {
    nodo->valor = valor;
    nodo->prox = prox;
    nodo->ant = NULL;
}

void inicializar_nodo_fim(nodo_deque* nodo, int valor, nodo_deque* ant) {
    nodo->valor = valor;
    nodo->prox = NULL;
    nodo->ant = ant;
}

void inserir_inicio(deque* d, int valor) {
    if (!d) {
        fprintf(stderr, "Erro(inserir_fim): ponteiro para deque é NULL.\n");
        return;
    }
    // Aloca memória para um novo nodo
    nodo_deque* novo_nodo = (nodo_deque*)malloc(sizeof(nodo_deque));

    inicializar_nodo_inicio(novo_nodo, valor, d->inicio);

    // Atualiza os ponteiros do deque
    if (d->inicio != NULL) {
        d->inicio->ant = novo_nodo;
    }
    d->inicio = novo_nodo;

    // Se o deque estava vazio, o novo nodo também é o fim do deque
    if (esta_vazio(d)) {
        d->fim = novo_nodo;
    }
    d->tamanho++;
}

void inserir_fim(deque* d, int valor) {
    if (!d) {
        fprintf(stderr, "Erro(inserir_fim): ponteiro para deque é NULL.\n");
        return;
    }
    // Aloca memória para um novo nodo
    nodo_deque* novo_nodo = (nodo_deque*)malloc(sizeof(nodo_deque));

    inicializar_nodo_fim(novo_nodo, valor, d->fim);

    // Atualiza os ponteiros do deque
    if (d->fim != NULL) {
        d->fim->prox = novo_nodo;
    }
    d->fim = novo_nodo;

    // Se o deque estava vazio, o novo nodo também é o início do deque
    if (esta_vazio(d)) {
        d->inicio = novo_nodo;
    }
    d->tamanho++;
}

bool esta_vazio(deque* d) {
    if (!d) {
        fprintf(stderr, "Erro(esta_vazio): ponteiro para deque é NULL.\n");
        return 1; // Considera um deque NULL como vazio
    }
    return d->tamanho == 0;
}

void remover_inicio(deque* d) {
    nodo_deque* temp = d->inicio;

    if (!d || esta_vazio(d)) {
        fprintf(stderr, "Erro(remover_inicio): deque está vazio ou é NULL.\n");
        return;
    }
    
    d->inicio = d->inicio->prox;

    if (d->inicio != NULL) {
        d->inicio->ant = NULL;
    } else {
        // Se o deque ficou vazio, atualiza o fim
        d->fim = NULL; 
    }
    free(temp);
    d->tamanho--;
}

void remover_fim(deque* d) {
    nodo_deque* temp = d->fim;

    if (!d || esta_vazio(d)) {
        fprintf(stderr, "Erro(remover_fim): deque está vazio ou é NULL.\n");
        return;
    }
    
    d->fim = d->fim->ant;

    if (d->fim != NULL) {
        d->fim->prox = NULL;
    } else {
        // Se o deque ficou vazio, atualiza o início
        d->inicio = NULL; 
    }

    free(temp);
    d->tamanho--;
}

int obter_inicio(deque* d) {
    if (!d || esta_vazio(d)) {
        fprintf(stderr, "Erro(obter_inicio): deque está vazio ou é NULL.\n");
        // Retorna um valor inválido para indicar erro
        return -1; 
    }
    return d->inicio->valor;
}

int obter_fim(deque* d) {
    if (!d || esta_vazio(d)) {
        fprintf(stderr, "Erro(obter_fim): deque está vazio ou é NULL.\n");
        // Retorna um valor inválido para indicar erro
        return -1; 
    }
    return d->fim->valor;
}

int obter_tamanho(deque* d) {
    if (!d) {
        fprintf(stderr, "Erro(obter_tamanho): ponteiro para deque é NULL.\n");
        // Retorna um valor inválido para indicar erro
        return -1; 
    }
    return d->tamanho;
}

void liberar_deque(deque* d) {
    nodo_deque* atual = d->inicio;
    nodo_deque* temp;

    if (!d) {
        fprintf(stderr, "Erro (liberar_deque): ponteiro para deque é NULL.\n");
        return;
    }
    
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    d->inicio = NULL;
    d->fim = NULL;
    d->tamanho = 0;
}

void imprimir_deque(deque* d) {
    nodo_deque* atual = d->inicio;

    if (!d) {
        fprintf(stderr, "Erro: ponteiro para deque é NULL.\n");
        return;
    }
    
    printf("Deque: ");
    while (atual->prox != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("%d\n", atual->valor);
}