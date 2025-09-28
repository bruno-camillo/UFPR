/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
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

long aleat (long min, long max) {
  return rand() % (max - min) + min;
}

long mdc (long a, long b) {
  if (a % b == 0)
  	return b;
  return mdc (b, a % b);
}

long mmc (long a, long b) {
  return (a * b) / mdc (a, b);
}

struct racional simplifica_r (struct racional r) {
	long m = mdc (r.num, r.den);
	r.num = r.num / m;
	r.den = r.den / m;
	if (r.den < 0) {
		r.num = -r.num;
		r.den = -r.den } 

  return r;
}

struct racional cria_r (long numerador, long denominador) {
	struct racional r;
	r.num = numerador;
	r.den = denominador;
	
	return r;	
}

int valido_r (struct racional r) {
	if (r.den = 0)
		return 0;
	return 1;
}

struct racional sorteia_r (long min, long max) {
	struct racional r;
	r.num = aleat (min, max);
	r.den = aleat (min, max);
	r = simplifica_r (r);
	
	return r;
}

void imprime_r (struct racional r) {
	if (valido_r (r)) {
		if (r.num == 0)
			printf ("0");
		else
			if (r.den == 1)
				printf ("%ld", r.num);
			else
				if (r.den == r.num) 
					printf ("1");
				else
					printf ("%ld/%ld", r.num, r.den);
	}
	else 
		printf ("INVALIDO\n");
}

struct racional soma_r (struct racional r1, struct racional r2) {
	struct racional soma;
	soma.den = mmc (r1.den, r2.den);
	soma.num = (soma.den / r1.den) * r1.num + (soma.den / r2.den) * r2.num;
	
	return simplifica_r (soma);
}

struct racional subtrai_r (struct racional r1, struct racional r2){
    struct racional soma;
    soma.den = mmc (r1.den, r2.den);
   	soma.num = (soma.den / r1.den) * r1.num - (soma.den / r2.den) * r2.num;
	
   	return simplifica_r (soma);
}

struct racional multiplica_r (struct racional r1, struct racional r2){
    struct racional produto;
    produto.num = r1.num * r2.num;
    produto.den = r1.den * r2.den;
    
    return simplifica_r (produto);    
}

struct racional divide_r (struct racional r1, struct racional r2){
    struct racional quociente;
    quociente.num = r1.num * r2.den;
    quociente.den = r1.den * r2.num;

    return simplifica_r (quociente);
}

void imprime_operacoes (int n, int min, int max, struct racional r1, struct racional r2) {
    for (int i = 1; i <= n; i++){
        printf ("%d: ", i);
        r1 = sorteia_r (min, max);
        r2 = sorteia_r (min, max);
       
        /*IMPRIME OS DOIS RACIONAIS SORTEADOS SE FOREM VALIDOS, IMPRIMINDO 
          INVALIDO CASO CONTRARIO.*/  
        imprime_r (r1);
        imprime_r (r2);
            
        if (!valido_r (r1) || !valido_r (r2)){
            printf(" NUMERO INVALIDO\n");
            break;
        }
        /*IMPRIME AS OPERACOES SE R2 FOR DIFERENTE DE ZERO, CASO CONTRARIO, 
         * IMPRIME DIVISAO INVALIDA E VOLTA NO LACO.*/
        if (r2.num == 0){
            printf (" DIVISAO INVALIDA\n");
            break;
        }

        else {
        imprime_r( soma_r(r1,r2) ); 
        imprime_r( subtrai_r(r1,r2) ); 
        imprime_r( multiplica_r(r1,r2) ); 
        imprime_r( divide_r(r1,r2) );
        } 
        
        printf ("\n");
        } 
}
