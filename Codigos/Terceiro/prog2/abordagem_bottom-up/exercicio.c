#include <stdio.h>
#include <stdlib.h>
#include "~/UFPR/Codigos/Segudo_Periodo/Prog_1/tp4/lista.h"

typedef struct {
    int id;
    int valor;
} produto;

typedef struct {
    produto *produtos;
    int tamanho;
} compra;

void gera_nota_fiscal(produto *produtos, int n) {
    printf("Nota Fiscal:\n");
    for (int i = 0; i < n; i++) {
        printf("Produto ID: %d, Valor: %d\n", produtos[i].id, produtos[i].valor);
    }
}

void insere_produto(compra *c, int id, int valor) {
    //c->produtos = realloc(c->produtos, (c->tamanho + 1) * sizeof(produto));
    c->produtos[c->tamanho].id = id;
    c->produtos[c->tamanho].valor = valor;
    c->tamanho++;
}

int valor_total(compra *c) {
    int total = 0;
    for (int i = 0; i < c->tamanho; i++) {
        total += c->produtos[i].valor;
    }
    return total;
}