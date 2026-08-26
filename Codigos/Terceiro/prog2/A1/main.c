#include <stdio.h>
#include <string.h>
#include "gbv.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <opção> <biblioteca> [documentos...]\n", argv[0]);
        return 1;
    }

    const char *opcao = argv[1];
    const char *nome_biblioteca = argv[2];

    Biblioteca bib;
    if (gbv_abrir(&bib, nome_biblioteca) != 0) {
        printf("Erro ao abrir biblioteca %s\n", nome_biblioteca);
        return 1;
    }

    if (strcmp(opcao, "-a") == 0) {
        for (int i = 3; i < argc; i++) {
            gbv_adicionar(&bib, nome_biblioteca, argv[i]);
        }
    } else if (strcmp(opcao, "-r") == 0) {
        for (int i = 3; i < argc; i++) {
            gbv_remover(&bib, argv[i]);
        }
    } else if (strcmp(opcao, "-l") == 0) {
        gbv_listar(&bib);
    } else if (strcmp(opcao, "-v") == 0 && argc >= 4) {
        gbv_visualizar(&bib, argv[3]);
    } else if (strcmp(opcao, "-o") == 0 && argc >= 4) {
        gbv_ordenar(&bib, nome_biblioteca, argv[3]);
    } else {
        printf("Opção inválida.\n");
    }

    return 0;
}