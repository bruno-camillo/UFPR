#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t newtonRaphson (Polinomio p, real_t x0, int criterioParada, int *it, real_t *raiz)
{

}


// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t bisseccao (Polinomio p, real_t a, real_t b, int criterioParada, int *it, real_t *raiz) {

}


void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx) {
    double b = p.p[p.grau];
    double c = b;

    for (int i = p.grau -1; i; --i){
        b = p.p[i] + + b * x;
        c = b + c * x;
    }

    b = p.p[0] + b * x;
    *px = b;
    *dpx = c;
}


void calcPolinomio_lento(Polinomio p, real_t x, real_t *px, real_t *dpx){
    real_t b = 0, c = 0;

    for (int i = p.grau; i; --i){
        b += p.p[i] * pow(x,i);
        c += i * p.p[i] * pow(x, i-1);
    }

    b += p.p[0];

    *px = b;
    *dpx = c;
}
