/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 * Atualizado em 09/09/2025 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b) {
    if (a % b == 0)
  		return b;
    return mdc (b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)  {
   return (a * b) / mdc (a, b);
}

int valido_r (struct racional *r) {
	if (r -> den == 0) 
		return 0;
	return 1;
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r (struct racional *r) {
    if (valido_r (r)) {
		long m = mdc (r -> num, r -> den);

		r -> num = r -> num / m;
		r -> den = r -> den / m;

		if (r -> den < 0) {
			r -> num = -r -> num;
			r -> den = -r -> den; 
        } 
	}

    if ( (r -> den == 0) || (r == NULL) )
		return 0;
	return 1;
}

long numerador_r (struct racional *r) {
    return r -> num;
}

long denominador_r (struct racional *r) {
    return r -> den;
}

struct racional *cria_r (long numerador, long denominador) {
    struct racional *r;
    /* aloca memoria para o racional */
    r = malloc (sizeof (struct racional));

    r -> num = numerador;
    r -> den = denominador;

    if (r == NULL)
        return NULL;
    return r;
}

void destroi_r (struct racional **r) {
    free (*r);
    *r = NULL;
}

void imprime_r (struct racional *r) {
    /* ponteiro nulo */
    if  (r == NULL) {
        printf ("NULL");
        return;
    }

    /* racional invalido */
    if (r -> den == 0) {
        printf ("NaN");
        return;
    }

    /* numerador 0 */
    if (r -> num == 0){
        printf ("0");
        return;
    }

    /* denominador 1 */
    if (r -> den == 1) {
        printf ("%ld", r -> num);
        return;
    }

    /* numerador e denominador iguais */
    if (r -> num == r -> den) {
        printf ("1");
        return;
    }

    /* racional em forma de fração */
    printf ("%ld/%ld", r -> num, r -> den);
}

int compara_r (struct racional *r1, struct racional *r2) {
    /* algum racional invalido ou nulo */
    if ( (!valido_r (r1) || !valido_r (r2)) || (r1 == NULL || r2 == NULL) )
	    return -2;

    /* r1 < r2 */
	if (r1 -> num * r2 -> den < r2 -> num * r1 -> den)
		return -1;

    /* r1 < r2 */
	if (r1 -> num * r2 -> den > r2 -> num * r1 -> den)
		return 1;

    /* r1 = r2 */
	return 0;
}

int soma_r (struct racional *r1, struct racional *r2, struct racional *r3) {
    /* denominador deve ser igual ao mcc dos racionais */
    r3 -> den = mmc (r1 -> den, r2 -> den);
    /* calculo do numerador */
	r3 -> num = (r3 -> den / r1 -> den) * r1 -> num + (r3 -> den / r2 -> den) * r2 -> num;

    simplifica_r (r3);

	if ( ((r3 -> den == 0) || (r3 -> num == 0)) || (r1 == NULL || r2 == NULL) )
		return 0;
	return 1;
}

int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3) {
    /* denominador deve ser igual ao mcc dos racionais */
    r3 -> den = mmc (r1 -> den, r2 -> den);
    /* calculo do numerador */
	r3 -> num = (r3 -> den / r1 -> den) * r1 -> num - (r3 -> den / r2 -> den) * r2 -> num;

	simplifica_r (r3);

	if ( ((r3 -> den == 0) || (r3 -> num == 0)) || (r1 == NULL || r2 == NULL) )
		return 0;
	return 1;
}

int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3) {
    /* calculo do numerador e denominador */ 
    r3 -> num = r1 -> num * r2 -> num;
	r3 -> den = r1 -> den * r2 -> den;

    simplifica_r (r3);

	if ( ((r3 -> den == 0) || (r3 -> num == 0)) || (r1 == NULL || r2 == NULL) )
		return 0;
	return 1;
}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3) {
    /* calculo do numerador e denominador multiplicando pelo inverso */
    r3 -> num = r1 -> num * r2 -> den;
	r3 -> den = r1 -> den * r2 -> num;

    simplifica_r (r3);
    
	if ( ((r3 -> den == 0) || (r3 -> num == 0)) || (r1 == NULL || r2 == NULL) )
		return 0;
	return 1;
}