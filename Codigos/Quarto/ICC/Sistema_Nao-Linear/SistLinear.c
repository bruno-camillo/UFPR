/*******************
  Sistemas Lineares 
********************/

#include <stdlib.h>
#include "SistLinear.h"

// cria um SistLinear_t *SL := (Ax = b) de dimensão n
SistLinear_t *criaSistLinear(double **A, double *b, unsigned int n) {

  SistLinear_t *SL = (SistLinear_t *) malloc(sizeof(SistLinear_t));
  SL->n = n;
  SL->A = A;
  SL->b = b;

  return SL;
}

void destroiSistLinear(SistLinear_t *SL) {
  free(SL);
}
