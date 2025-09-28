/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

int simplifica_r (struct racional *r);

/* preenche o vetor v de tamanho n com racionais 
 * le o numerador e o denominador de cada elemento */
void preenche_vetor (struct racional **v, int n) {
    for (int i = 0; i < n; i++){
        long num, den;
        scanf ("%ld %ld", &num, &den);

        struct racional *r = cria_r (num, den);
        simplifica_r (r);

        v[i] = r;
    }
}

/* imprime o vetor v de tamanho n */
void imprime_vetor (struct racional **v, int n) {
    printf ("VETOR = ");

    for (int i = 0; i < n; i++) {
        /* imprime espaco antes do elemento, exceto no primeiro */
        if (i > 0) 
            printf (" ");
        imprime_r (v[i]);
    }

    printf ("\n");
}

/* elimina do vetor v de tamanho n os racionais inválidos
 * atualiza o tamanho do vetor n */
void elimina_do_vetor (struct racional **v, int *n) {
    int i = 0;

	/* percorre o vetor e elimina os racionais invalidos */
    while (i < *n) 
        if (!valido_r (v[i])) {
            /*desaloca memoria do elemento eliminado*/
            destroi_r (&v[i]);
			/* troca o elemento invalido com o ultimo elemento */
            v[i] = v[*n - 1];
            (*n)--;
        } 
        else
            i++; //incrementa se o elemento for valido
}

/* ordena o vetor v de tamanho n em ordem crescente */
void ordena_vetor (struct racional **v, int n) {
	int indice_menor;
	struct racional *aux;

    /* percorre o vetor e ordena os elementos */
	for (int i = 0; i < n; i++) {
		indice_menor = i;
        /* procura o menor elemento no vetor */
		for (int j = i + 1; j < n; j++)
        /* se v[j] < v[indice_menor], o indice eh alterado */
			if (compara_r (v[j], v[indice_menor]) == -1)
				indice_menor = j;

        /* troca o elemento atual com o menor elemento encontrado */
        if (indice_menor != i ){  
	        aux = v[indice_menor];
		    v[indice_menor] = v[i];
		    v[i] = aux;
        }
	}
} 

/* calcula a soma dos racionais do vetor v e imprime o resultado */
void soma_do_vetor (struct racional **v, int n) {
	struct racional *soma = malloc (sizeof (struct racional));
    
    /* inicializa a soma com 0 */
	soma -> num = 0;
	soma -> den = 1;

    struct racional *aux = malloc (sizeof (struct racional));
	/* percorre o vetor e soma os elementos */
	for (int i = 0; i < n; i++) {
        aux -> num = soma -> num;
        aux -> den = soma -> den;

        soma_r (aux, v[i], soma);
    }
	simplifica_r (soma);
    
	/* imprime o resultado */
	printf ("SOMA = ");
	imprime_r (soma);
	printf ("\n");

    destroi_r (&soma);
    destroi_r (&aux);
}

/* libera a memória alocada para os racionais do vetor v */
void libera_vetor (struct racional **v, int n) {
    for (int i = 0; i < n; i++) 
        destroi_r (&v[i]);
}

/* programa principal */
int main () {
	int n;
    scanf ("%d", &n);

    struct racional **vet = malloc (sizeof (struct racional) * n);

    preenche_vetor (vet, n);
    imprime_vetor (vet, n);

    elimina_do_vetor (vet, &n);
    imprime_vetor (vet, n);
    
    ordena_vetor (vet, n);
    imprime_vetor (vet, n);

    soma_do_vetor (vet, n);

    libera_vetor (vet, n);

    /* imprime o vetor nulo */
    imprime_vetor (vet, n); 

    free (vet);
    vet = NULL;

    return 0;
}