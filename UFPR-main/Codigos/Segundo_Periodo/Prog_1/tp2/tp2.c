/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

long mdc (long a, long b);

struct racional simplifica_r (struct racional r);

/* Preenche o vetor v com n racionais lidos da entrada padrão.
 * Cada racional é lido na forma "num den", ou seja, numerador e
 * denominador separados por espaço em branco. */
void preenche_vetor (struct racional v[], int n) {
    for (int i = 0; i < n; i++) {
        long num, den;
        scanf ("%ld %ld", &num, &den);
        v[i] = simplifica_r (cria_r (num, den));
    }
}

/* Imprime o vetor v com n racionais, todos na mesma linha,
 * separados por espaço em branco e com uma quebra de linha no final.
 * Antes do vetor, imprima a mensagem "VETOR = ". */
void imprime_vetor (struct racional v[], int n) {
    printf ("VETOR =");
    for (int i = 0; i < n; i++)
        imprime_r (v[i]);
    
    printf ("\n");
}

/* Elimina do vetor v com n racionais todos os racionais inválidos.
 * A função deve alterar o valor de n para refletir o novo tamanho do vetor. */
void elimina_do_vetor (struct racional v[], int *n) {
    int i;
	/* percorre o vetor e elimina os racionais invalidos */
    for (i = 0; i < (*n); i++) {
        if (!valido_r (v[i])) {
			/* desloca os elementos a partir de i para a esquerda */
            for (int j = i; j < (*n) - 1; j++)
                v[j] = v[j + 1];
            (*n)--;
            i--;
        }
    }
    imprime_vetor (v, *n);
}

/* ordena o vetor pelo metodo de Selection Sort */
void ordena_vetor (struct racional v[], int n) {
	int i, j, indice_menor;
	struct racional aux;

    /* percorre o vetor e ordena os elementos */
	for (i = 0; i < n; i++) {
		indice_menor = i;
		for (j = i + 1; j < n; j++)
        /* compara_r retorna -1 se r1 < r2 */
			if (compara_r (v[j], v[indice_menor]) == -1)
				indice_menor = j;
        if (indice_menor != i ){  
	        aux = v[indice_menor];
		    v[indice_menor] = v[i];
		    v[i] = aux;
        }
	}
    imprime_vetor (v, n);
} 
/* soma os elementos do vetor e imprime o resultado */
void soma_do_vetor (struct racional v[], int n) {
	int i;
	struct racional *soma = malloc (sizeof (struct racional));
    
    /* inicializa a soma com 0 */
	soma -> num = 0;
	soma -> den = 1;

	/* percorre o vetor e soma os elementos */
	for (i =0; i < n; i++)
		soma_r (*soma, v[i], soma);

	*soma = simplifica_r (*soma);
	/* imprime o resultado */
	printf ("SOMA =");
	imprime_r (*soma);
	printf ("\n");
	free (soma);
}

/* programa principal */
int main () {
    struct racional v[100];
    int n;
    int *valor_n = &n;

    scanf ("%d", &n);

    preenche_vetor (v, n);
    imprime_vetor (v, n);
    elimina_do_vetor (v, valor_n);
    ordena_vetor (v, n);
    soma_do_vetor (v, n);

  return (0) ;
}