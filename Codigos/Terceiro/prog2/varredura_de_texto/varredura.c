#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct palavra {
    char * string;
    int qnt_reps;
} palavra;

// busca uma palavra repetida num vetor de palavras(struct)
// retorna 1 caso encontre, -1 caso contrario
// retorna 0 em caso de erro
int busca_repetido(palavra* vet, char* str) {
    char* atual;
    int i = 0;
    if (!vet || !str)
        return 0;

    atual = vet[i].string;    
    while (atual != NULL && strcmp(atual, str) != 0) {
        i++;
        atual = vet[i].string;
    }

    if (strcmp(atual, str) == 0)
        return 1;
    return 0;

}

// busca a palavra mais vezes repetidas dentro do vetor
// retorna o indice da palavra que mais se repete
int busca_mais_repetido (palavra* vet) {
    int maior = 0;

    if(!vet)
        return 0;

    for (int i = 0; i < 10; i++) {
        if (vet[i].string != NULL)
            if(vet[i].qnt_reps > maior)
                maior = i;
    }

    return maior;
}

int main() {
    FILE* file = fopen("texto.txt", "r");
    //vetor onde vao se armazenar as palavras
    palavra vet_palavras[10];
    char delimitador[] = ", .;:?!";
    char* palavra_atual;
    char texto[100];
    int i = 0, indice_rep, indice_maior;

    // erro no arquivo
    if (file == NULL)
        return printf("ERRO");

    fgets(texto, sizeof(texto), file);

    palavra_atual = strtok(texto, delimitador);

    vet_palavras[i].string = palavra_atual;
    vet_palavras[i].qnt_reps = vet_palavras[i].qnt_reps + 1;
    i++;

    palavra_atual = strtok(NULL, delimitador);

    while (palavra_atual != NULL) {
        indice_rep = busca_repetido(vet_palavras, palavra_atual);

        if (indice_rep == -1) {
            vet_palavras[i].string = palavra_atual;
            vet_palavras[i].qnt_reps = 1;
            i++;
        } 
        else vet_palavras[indice_rep].qnt_reps++;
        
        palavra_atual = strtok(NULL, delimitador);
    }

    indice_maior = busca_mais_repetido(vet_palavras);
    printf("A palavra que mais se repete eh '%s' e repete %d vezes\n", 
    vet_palavras[indice_maior].string, vet_palavras[indice_maior].qnt_reps);

    return 1;
}