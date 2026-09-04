/*******************************************************************************
  Solução de Sistemas Não Lineares por Eliminação de Gauss
*******************************************************************************/

#ifndef __NEWTON_SNL__
#define __NEWTON_SNL__

#include "SistNaoLinear.h"

/*
* Aplica o método de newton para resolver o Sistema Não Linear SNL -> resultado em X
* X: aproximação inicial
* epsilon_x: tolerância no eixo x
* epsilon_y: tolerância no eixo y
* MAXIT: número máximo de iterações
* Ttotal: tempo gasto total
* Tgauss: tempo gasto nas eliminações de gauss
* Tjacobiana: tempo gasto nas computações da matriz jacobiana
*
* Devolve 0 caso tenha atendido critério de parada e -1 se atingiu MAXIT
*/ 
int newton(SistNaoLinear_t *SNL, double *X, double epsilon_x, double epsilon_y,
                int MAXIT, double *Ttotal, double *Tgauss, double *Tjacobiana);

// define o calculo da norma do vetor V de tamanho n
// Aqui: norma infinito
double norma(double *V, unsigned int n);


#endif

