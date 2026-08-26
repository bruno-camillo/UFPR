#include <stdio.h>
#include <string.h>
#include "gbv.h"

int main(int argc, char *argv[]) {
    // Agora o minimo de argumentos eh 4: ./gbv <chave> <opcao> <biblioteca>
    if (argc < 4) {
        printf("Uso: %s <chave> <opcao> <biblioteca> [documentos...]\n", argv[0]);
        return 1;
    }

    const char *chave = argv[1];
    const char *opcao = argv[2];
    const char *nome_biblioteca = argv[3];

    // Validacao basica do tamanho da chave no terminal
    if (strlen(chave) != 4) {
        printf("Erro: A chave deve ter exatamente 4 caracteres.\n");
        return 1;
    }

    Biblioteca bib;
    
    // gbv_abrir agora valida a chave internamente
    if (gbv_abrir(&bib, nome_biblioteca, chave) != 0) {
        // Se falhar (por ex: Acesso Negado), encerra a execucao imediatamente
        return 1;
    }

    // Os documentos e criterios agora comecam a partir do indice 4 devido a nova ordem
    if (strcmp(opcao, "-a") == 0) {
        for (int i = 4; i < argc; i++) {
            gbv_adicionar(&bib, nome_biblioteca, argv[i]);
        }
    } else if (strcmp(opcao, "-r") == 0) {
        for (int i = 4; i < argc; i++) {
            gbv_remover(&bib, argv[i]);
        }
    } else if (strcmp(opcao, "-l") == 0) {
        gbv_listar(&bib);
    } else if (strcmp(opcao, "-v") == 0 && argc >= 5) {
        gbv_visualizar(&bib, argv[4]);
    } else if (strcmp(opcao, "-o") == 0 && argc >= 5) {
        gbv_ordenar(&bib, nome_biblioteca, argv[4]);
    } else {
        printf("Opção inválida.\n");
    }

    return 0;
}