#ifndef GBV_H
#define GBV_H

#include <time.h>

#define MAX_NOME 256
#define TAMANHO_BUFFER 512   // tamanho fixo do buffer em bytes

// Estrutura de metadados de cada documento
typedef struct {
    char nome[MAX_NOME];   // nome do documento
    long tamanho;          // tamanho em bytes
    time_t data;           // data de inserção
    long deslocamento;     // posição no container
} Documento;

// Estrutura que representa a biblioteca (diretório em memória)
typedef struct {
    Documento *documentos; // vetor de documentos
    int quantidade;        // número de documentos
} Biblioteca;

// Funções que você deve implementar em gbv.c
int gbv_criar(const char *nome_arquivo, const char *chave);

int gbv_abrir(Biblioteca *bib, const char *nome_arquivo, const char *chave);

int gbv_adicionar(Biblioteca *bib, const char *container, const char *nome_documento);

int gbv_remover(Biblioteca *bib, const char *nome_documento);

int gbv_listar(const Biblioteca *bib);

int gbv_visualizar(const Biblioteca *bib, const char *nome_documento);

int gbv_ordenar(Biblioteca *bib, const char *container, const char *criterio);

#endif