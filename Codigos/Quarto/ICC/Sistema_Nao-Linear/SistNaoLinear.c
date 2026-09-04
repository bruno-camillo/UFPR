/*******************************************************************************
  Solução de Sistemas Lineares por Eliminação de Gauss
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "SistNaoLinear.h"
#include "utils.h"

// retorna um SNL de dimensão n.
// f: cada linha dessa matriz contém a expressão de uma função do SNL.
// considera que as variáveis se chamam x1, x2, ..., xn
SistNaoLinear_t *criaSistNaoLinear(char **f, unsigned int n, double *Tderivadas) {

  SistNaoLinear_t *SNL = (SistNaoLinear_t *) malloc(sizeof(SistNaoLinear_t));
  SNL->n = n;
  SNL->F = (void **) malloc(sizeof(void *)*n);
  SNL->J = (void ***) malloc(sizeof(void **)*n);
  SNL->var = (char **) malloc(sizeof(char *)*n);
  for (int i = 0; i < n; ++i) {
    SNL->J[i] = (void **) malloc(sizeof(void *)*n);
    SNL->var[i] = (char *) malloc(sizeof(char)*MAXLEN_VARS);
    SNL->var[i][0] = 'x';
    sprintf(&(SNL->var[i][1]), "%d", i+1);
  }

  // cria funções com libmatheval
  *Tderivadas = timestamp();
  for (int i = 0; i < n; ++i) {
    SNL->F[i] = evaluator_create(f[i]);
    for (int j = 0; j < n; ++j)
      SNL->J[i][j] = evaluator_derivative(SNL->F[i], SNL->var[j]);
  }
  *Tderivadas = timestamp() - *Tderivadas;

  return SNL;
}

void destroiSistNaoLinear(SistNaoLinear_t *SNL) {
  for (int i = 0; i < SNL->n; ++i) {
    for (int j = 0; j < SNL->n; ++j)
      evaluator_destroy(SNL->J[i][j]);
    evaluator_destroy(SNL->F[i]);
    free(SNL->J[i]);
    free(SNL->var[i]);
  }
  free(SNL->var);
  free(SNL->F);
  free(SNL->J);
  free(SNL);
}

// calcula o valor de cada função do SNL com o vetor de variáveis X -> resultado em FX
void calcF(double *FX, SistNaoLinear_t *SNL, double *X) {
  for (int i = 0; i < SNL->n; ++i)
    FX[i] = evaluator_evaluate(SNL->F[i], SNL->n, SNL->var, X);
}

// calcula o valor da matriz Jacobiana com o vetor de variáveis X -> resultado em JX
void calcJ(double **JX, SistNaoLinear_t *SNL, double *X) {
  for (int i = 0; i < SNL->n; ++i)
    for (int j = 0; j < SNL->n; ++j)
      JX[i][j] = evaluator_evaluate(SNL->J[i][j], SNL->n, SNL->var, X);
}

// imprime as funções com libmatheval
void printSistNaoLinear(SistNaoLinear_t *SNL) {

  printf("%d\n", SNL->n);
  for (int i = 0; i < SNL->n; ++i)
    printf("%s = 0\n", evaluator_get_string(SNL->F[i]));

/*
  printf("Variáveis:\n");
  for (int i = 0; i < SNL->n; ++i)
    printf("%s ", SNL->var[i]);
  printf("\n");

  printf("Sistema nao linear:\n");
  for (int i = 0; i < SNL->n; ++i)
    printf("%s = 0\n", evaluator_get_string(SNL->F[i]));

  printf("Jacobiana:\n");
  for (int i = 0; i < SNL->n; ++i) {
    for (int j = 0; j < SNL->n; ++j)
      printf("%s\t\t", evaluator_get_string(SNL->J[i][j]));
    printf("\n");
  }
*/
}

