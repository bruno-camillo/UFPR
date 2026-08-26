#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void inicializar_deque(deque* d) {
    if (!d) {
        fprintf(stderr, "Erro(inicializar_deque): ponteiro para deque é NULL.\n");
        return;
    }

    d->inicio = NULL;
    d->fim = NULL;
    d->tamanho = 0;
}

void inicializar_nodo_inicio(nodo_deque* nodo, ponto p, nodo_deque* prox) {
    nodo->p = p;
    nodo->prox = prox;
    nodo->ant = NULL;
}

void inicializar_nodo_fim(nodo_deque* nodo, ponto p, nodo_deque* ant) {
    nodo->p = p;
    nodo->prox = NULL;
    nodo->ant = ant;
}

void inserir_inicio(deque* d, ponto p) {
    if (!d) {
        fprintf(stderr, "Erro(inserir_inicio): ponteiro para deque é NULL.\n");
        return;
    }
    // Aloca memória para um novo nodo
    nodo_deque* novo_nodo = (nodo_deque*)malloc(sizeof(nodo_deque));

    inicializar_nodo_inicio(novo_nodo, p, d->inicio);

    // Atualiza os ponteiros do deque
    if (d->inicio != NULL) {
        d->inicio->ant = novo_nodo;
    }
    d->inicio = novo_nodo;

    // Se o deque estava vazio, o novo nodo também é o fim do deque
    if (d->fim == NULL) {
        d->fim = novo_nodo;
    }
    d->tamanho++;
}

void inserir_fim(deque* d, ponto p) {
    if (!d) {
        fprintf(stderr, "Erro(inserir_fim): ponteiro para deque é NULL.\n");
        return;
    }
    // Aloca memória para um novo nodo
    nodo_deque* novo_nodo = (nodo_deque*)malloc(sizeof(nodo_deque));

    inicializar_nodo_fim(novo_nodo, p, d->fim);

    // Atualiza os ponteiros do deque
    if (d->fim != NULL) {
        d->fim->prox = novo_nodo;
    }
    d->fim = novo_nodo;

    // Se o deque estava vazio, o novo nodo também é o início do deque
    if (d->inicio == NULL) {
        d->inicio = novo_nodo;
    }
    d->tamanho++;
}

bool esta_vazio(deque* d) {
    if (!d) {
        fprintf(stderr, "Erro(esta_vazio): ponteiro para deque é NULL.\n");
        return true; // Considera um deque NULL como vazio
    }
    return d->tamanho == 0;
}

void remover_inicio(deque* d) {
    if (!d || esta_vazio(d)) {
        fprintf(stderr, "Erro(remover_inicio): deque está vazio ou é NULL.\n");
        return;
    }

    nodo_deque* temp = d->inicio;
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
    if (!d || esta_vazio(d)) {
        fprintf(stderr, "Erro(remover_fim): deque está vazio ou é NULL.\n");
        return;
    }

    nodo_deque* temp = d->fim;
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

ponto* obter_inicio(deque* d) {
    if (!d || esta_vazio(d)) {
        fprintf(stderr, "Erro(obter_inicio): deque está vazio ou é NULL.\n");
        // Retorna um valor inválido para indicar erro
        return NULL; 
    }
    return &(d->inicio->p);
}

ponto* obter_fim(deque* d) {
    if (!d || esta_vazio(d)) {
        fprintf(stderr, "Erro(obter_fim): deque está vazio ou é NULL.\n");
        // Retorna um valor inválido para indicar erro
        return NULL; 
    }
    return &(d->fim->p);
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
    if (!d) {
        fprintf(stderr, "Erro (liberar_deque): ponteiro para deque é NULL.\n");
        return;
    }

    nodo_deque* atual = d->inicio;
    nodo_deque* temp;

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
    if (!d) {
        fprintf(stderr, "Erro: ponteiro para deque é NULL.\n");
        return;
    }
    
    nodo_deque* atual = d->inicio;
    
    printf("Deque: ");
    if (esta_vazio(d)) {
        printf("[VAZIO]\n");
        return;
    }
    
    printf("(%.1f, %.1f)", atual->p.x, atual->p.y);

    atual = atual->prox;

    while (atual != NULL) {
        printf(" (%.2f, %.2f)", atual->p.x, atual->p.y);
        atual = atual->prox;
    }

    printf("\n");
}