/*
    Método de Newton para a resolução de Sistemas Não Lineares nxn

    prof. Guilherme A. Derenievicz (DINF/ET/UFPR)

    Entrada:
    <n>
    <exp f1(x)>
    <exp f2(x)>
    ...
    <exp fn(x)>
    <aproximação inicial x1>
    <aproximação inicial x2>
    ...
    <aproximação inicial xn>
    <epsilon>
    <max iterações>

    Obs: variáveis devem ser x1, x2, ..., xn.

    TODO: desalocar memória
*/

#include <stdio.h>
#include <stdlib.h>
#include "SistNaoLinear.h"
#include "NewtonSNL.h"
#include "utils.h"

int main() {

  unsigned int n;
  double epsilon, *X, Ttotal, Tgauss, Tjacobiana, Tderivadas;
  int MAXIT;
  char **f;

  while (scanf("%d",&n) != EOF) {

    f = (char **) malloc(sizeof(char *)*n);
    for (int i = 0; i < n; ++i) {
      f[i] = (char *) malloc(sizeof(char)*MAXLEN_FUNCS);
      scanf("%s", f[i]);
    }

    X = (double *) malloc(sizeof(double)*n);

    for (int i = 0; i < n; ++i)
      scanf("%lf", &(X[i]));

    scanf("%lf %d", &epsilon, &MAXIT);

    SistNaoLinear_t *SNL = criaSistNaoLinear(f, n, &Tderivadas);
    printSistNaoLinear(SNL);

    newton(SNL, X, epsilon, epsilon, MAXIT, &Ttotal, &Tgauss, &Tjacobiana);

    printf("###########\n");
    printf("# Tempo Total: %lf ms\n", Ttotal);
    printf("# Tempo Derivadas: %lf ms\n", Tderivadas);
    printf("# Tempo Jacobiana: %lf ms\n", Tjacobiana);
    printf("# Tempo SL: %lf ms\n", Tgauss);
    printf("###########\n\n");

    destroiSistNaoLinear(SNL);
    free(X);
    for (int i = 0; i < n; ++i)
      free(f[i]);
    free(f);
  }

  return 0;
}

