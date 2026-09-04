/*******************************************************************************
  Solução de Sistemas Lineares por Eliminação de Gauss
*******************************************************************************/

#ifndef __SIST_NAO_LINEAR__
#define __SIST_NAO_LINEAR__

#include <stdlib.h>
#include <matheval.h>

#define MAXLEN_VARS 5     // tamanho máximo de nomes de variáveis (log(n))
#define MAXLEN_FUNCS 200  // tamanho máximo de expressões de funções

// n: dimensão do sistema não linear
// var: nomes das variáveis (x1, x2, ..., xn)
// F: vetor de ponteiros para as n funções
// J: matriz Jacobiana com as derivadas parciais de cada uma das n funções
typedef struct {
  unsigned int n;
  char **var;
  void **F;
  void ***J;
} SistNaoLinear_t;

// retorna um SNL de dimensão n.
// f: cada linha dessa matriz contém a expressão de uma função do SNL.
// considera que as variáveis se chamam x1, x2, ..., xn
// Tderivadas: tempo gasto no computo das derivadas parciais
SistNaoLinear_t *criaSistNaoLinear(char **f, unsigned int n, double *Tderivadas);

void destroiSistNaoLinear(SistNaoLinear_t *SNL);

// calcula o valor de cada função do SNL com o vetor de variáveis X -> resultado em FX
void calcF(double *FX, SistNaoLinear_t *SNL, double *X);

// calcula o valor da matriz Jacobiana com o vetor de variáveis X -> resultado em JX
void calcJ(double **JX, SistNaoLinear_t *SNL, double *X);

// imprime as funções com libmatheval
void printSistNaoLinear(SistNaoLinear_t *SNL);

#endif

