#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double real_t;

typedef struct {
  real_t *p;
  int grau;
} Polinomio;

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

    for (int i = p.grau; i >= 0 ; --i){
        b += p.p[i] * pow(x,i);
        c += i * p.p[i] * pow(x, i-1);
    }

    b += p.p[0];
    printf("valor de b: %f\n", b);
    *(px) = b;
    *(dpx) = c;
}

int main () {
    Polinomio pol;
    real_t *px = malloc(sizeof(real_t));
    real_t *dpx = malloc(sizeof(real_t));
    
    scanf("%d", &pol.grau);

    pol.p = malloc(sizeof(int) * pol.grau);

    for (int i=pol.grau; i >=0; --i)
        scanf("%lf", &pol.p[i]);

    calcPolinomio_lento(pol, 3, px, dpx);

    printf("Valor Polinomio: %.5f; Valor Derivada: %.5f\n");

    return 0;
}