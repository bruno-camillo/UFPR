/*******************************************************************************
  Solução de Sistemas Lineares por Eliminação de Gauss
*******************************************************************************/

#ifndef __ELIM_GAUSS__
#define __ELIM_GAUSS__

#include "SistLinear.h"

// eliminação de Gauss no sistema linear SL -> solução em X
void eliminacaoGauss(SistLinear_t *SL, double *X);

// triangularização
void triang(SistLinear_t *SL);

// retrossubstituição
void retrossubs(SistLinear_t *SL, double *X);

// Efetua pivoteamento parcial na linha i
void pivot(SistLinear_t *SL, int i);

#endif

