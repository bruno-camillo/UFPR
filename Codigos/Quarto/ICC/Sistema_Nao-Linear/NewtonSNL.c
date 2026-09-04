/*******************************************************************************
  Solução de Sistemas Não Lineares por Eliminação de Gauss
*******************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "NewtonSNL.h"
#include "SistLinear.h"
#include "EliminacaoGauss.h"
#include "SistNaoLinear.h"
#include "utils.h"

/*
* Aplica o método de newton para resolver o Sistema Não Linear SNL -> resultado em X
* X: aproximação inicial
* epsilon_x: tolerância no eixo x
* epsilon_y: tolerância no eixo y
* MAXIT: número máximo de iterações
* Ttotal: tempo gasto total
* Tgauss: tempo gasto nas eliminações de gauss
* Tjacobiana: tempo gasto nas computações da matriz jacobiana
*/ 
int newton(SistNaoLinear_t *SNL, double *X, double epsilon_x, double epsilon_y,
                int MAXIT, double *Ttotal, double *Tgauss, double *Tjacobiana) {

  *Tgauss = 0;
  *Tjacobiana = 0;
  *Ttotal = timestamp();

  // Aloca vetores e matrizes
  double *S = (double *) malloc(sizeof(double)*SNL->n);
  double *FX = (double *) malloc(sizeof(double)*SNL->n);
  double **JX = (double **) malloc(sizeof(double *)*SNL->n);
  for (int i = 0; i < SNL->n; ++i)
    JX[i] = (double *) malloc(sizeof(double)*SNL->n);

  printf("# 0\n");
  for (int i = 0; i < SNL->n; ++i)
    printf("x%d = %lf\n", i+1, X[i]);

  // loop de iterações
  for (int iter = 0; iter < MAXIT; ++iter) {

    calcF(FX, SNL, X);
    if (norma(FX, SNL->n) < epsilon_y) break;

    double tjacobiana = timestamp();
    calcJ(JX, SNL, X);
    tjacobiana = timestamp() - tjacobiana;
    *Tjacobiana = *Tjacobiana + tjacobiana;

    for (int i = 0; i < SNL->n; ++i)
      FX[i] = -FX[i];

    double tgauss = timestamp();
    SistLinear_t *SL = criaSistLinear(JX, FX, SNL->n); 
    eliminacaoGauss(SL, S);
    destroiSistLinear(SL);
    tgauss = timestamp() - tgauss;
    *Tgauss = *Tgauss + tgauss;

    for (int i = 0; i < SNL->n; ++i)
      X[i] += S[i];

    printf("# %d\n", iter+1);
    for (int i = 0; i < SNL->n; ++i)
      printf("x%d = %.10lf\n", i+1, X[i]); 

    if (norma(S, SNL->n) < epsilon_x) break;
  }

  *Ttotal = timestamp() - *Ttotal;

  for (int i = 0; i < SNL->n; ++i)
    free(JX[i]);
  free(S);
  free(FX);
  free(JX);

  return 0;
}

// define o calculo da norma do vetor V de tamanho n
// Aqui: norma infinito
double norma(double *V, unsigned int n) {
  double max = fabs(V[0]);
  for (int i = 1; i < n; ++i)
    if (fabs(V[i]) > max)
      max = fabs(V[i]);
  return max;
}

