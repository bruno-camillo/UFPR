/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"
/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* retorna um número aleatório entre min e max. */
long aleat (long min, long max) {
    return rand() % (max - min + 1) + min;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b) {
    if (a % b == 0)
  		return b;
    return mdc (b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b) {
    return (a * b) / mdc (a, b);
}

long numerador_r (struct racional r){
    return r.num;
}

long denominador_r (struct racional r){
    return r.den;
}

struct racional cria_r (long numerador, long denominador){
    struct racional r;
	
	r.num = numerador;
	r.den = denominador;
	
	return r;	
}

int valido_r (struct racional r) {
	if (r.den == 0) 
		return 0;
	return 1;
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r) {
	if (valido_r (r)) {
		long m = mdc (r.num, r.den);

		r.num = r.num / m;
		r.den = r.den / m;

		if (r.den < 0) {
			r.num = -r.num;
			r.den = -r.den; } 
	}

    return r;
}

struct racional sorteia_r (long min, long max) {
	struct racional r;
	
	/* seleciona aleatoriamente os valores do numerador e denominador */
	r.num = aleat (min, max);
	r.den = aleat (min, max);
	
	return simplifica_r (r);
}

void imprime_r (struct racional r) {
	if (valido_r (r)) {
		if (r.num == 0) {
			printf (" 0");
			return;
		}
		if (r.den == 1) {
			printf (" %ld", r.num);
			return;
		}
		if (r.den == r.num) { 
			printf (" 1");
			return;
		}
		printf (" %ld/%ld", r.num, r.den);
		return;
	}
	printf (" NaN");
	return;
}

int compara_r (struct racional r1, struct racional r2) {
	if (!valido_r (r1) || !valido_r (r2))
	    return -2;
	if (r1.num * r2.den < r2.num * r1.den)
		return -1;
	if (r1.num * r2.den > r2.num * r1.den)
		return 1;
	return 0;
}

int soma_r (struct racional r1, struct racional r2, struct racional *r3) {
	r3 -> den = mmc (r1.den, r2.den);
	r3 -> num = (r3 -> den / r1.den) * r1.num + (r3 -> den / r2.den) * r2.num;
	
	if ((r3 -> den == 0) || (r3 -> num == 0))
		return 0;
	return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3) {
	r3 -> den = mmc (r1.den, r2.den);
   	r3 -> num = (r3 -> den / r1.den) * r1.num - (r3 -> den / r2.den) * r2.num;

	if ((r3 -> den == 0) || (r3 -> num == 0))
		return 0;
	return 1;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3) {
	r3 -> num = r1.num * r2.num;
	r3 -> den = r1.den * r2.den;

	if ((r3 -> den == 0) || (r3 -> num == 0))
		return 0;
	return 1;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3) {
	r3 -> num = r1.num * r2.den;
	r3 -> den = r1.den * r2.num;

	if ((r3 -> den == 0) || (r3 -> num == 0))
		return 0;
	return 1;
}
