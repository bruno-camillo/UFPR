/*******************
  Sistemas Lineares 
********************/

#ifndef __SIST_LINEAR__
#define __SIST_LINEAR__

// Sistema Linear Ax = b de dimensão n
typedef struct {
  unsigned int n;
  double **A;
  double *b;
} SistLinear_t;

// cria um SistLinear_t *SL := (Ax = b) de dimensão n
SistLinear_t *criaSistLinear(double **A, double *b, unsigned int n);

void destroiSistLinear(SistLinear_t *SL);

#endif
