#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
typedef struct ponto {
    float x;                
    float y;               
    int id;                 
    float erro;            
} ponto;

// prototipos de dados para o deque (lista duplamente encadeada)

// descreve um nodo do deque
typedef struct nodo_deque {
    ponto p; // ponto armazenado no nodo
    struct nodo_deque* prox; // ponteiro para o próximo nodo 
    struct nodo_deque* ant; // ponteiro para o nodo anterior
} nodo_deque;

// descreve o deque
typedef struct deque {
    nodo_deque* inicio; // ponteiro para o início do deque
    nodo_deque* fim; // ponteiro para o fim do deque
    int tamanho; // número de elementos no deque
} deque;

// protótipos das funções para manipular o deque

// inicializa um deque vazio
void inicializar_deque(deque* d);

// insere um elemento no início do deque
void inserir_inicio(deque* d, ponto p);

// insere um elemento no fim do deque
void inserir_fim(deque* d, ponto p);

// remove um elemento do início do deque
void remover_inicio(deque* d);

// remove um elemento do fim do deque
void remover_fim(deque* d); 

// retorna o valor do elemento no início do deque
ponto* obter_inicio(deque* d);

// retorna o valor do elemento no fim do deque
ponto* obter_fim(deque* d);

// retorna o número de elementos no deque
int obter_tamanho(deque* d);

// verifica se o deque está vazio
bool esta_vazio(deque* d);

// libera a memória alocada para o deque
void liberar_deque(deque* d);

// imprime os elementos do deque
void imprimir_deque(deque* d);

// inicializa o nodo inserido no inicio do deque
void inicializar_nodo_inicio(nodo_deque* nodo, ponto p, nodo_deque* prox);

// inicializa o nodo inserido no fim do deque
void inicializar_nodo_fim(nodo_deque* nodo, ponto p, nodo_deque* ant);

#endif
