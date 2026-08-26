#ifndef CALCULO_H
#define CALCULO_H

#include "lista.h"

/* calcula a area do triangulo formado pelos pontos (x1,y1), (x2,y2)
// e (x3,y3), usando o valor absoluto do determinante da matrix com
// os 3 pontos dividido por 2 */
float area_triangulo(float x1, float y1, 
                     float x2, float y2, 
                     float x3, float y3);


/* calula a altura do triangulo elevada ao quadrado, sendo a altura
a distancia entre (x2,y2) e a base do triangulo (x1,y1)~(x3,y3)
considerando a equacao: area = (base * altura) / 2
elevando ao quadrado: area^2 = (base^2 * altura^2) / 4
reorganizando:      altura^2 = 4 * area^2 / base^2 */

float altura2_triangulo(float x1, float y1, 
                        float x2, float y2, 
                        float x3, float y3);

/* Ponteiro para função que aponta para algum dos dois calculos de área possivel
    - Receba 6 floats e retorne 1 float. */
typedef float (*FuncaoErro)(float, float, float, float, float, float);

/* Função que recebe:
    - Ponteiro para Vizinho Esquerdo
    - Ponteiro para Ponto Atual
    - Ponteiro para Vizinho Direito
    - Ponteiro para função de cálculo
   Retorna 
    - Float de erro do Ponto Atual
*/
float calcular_erro(Ponto *esq, Ponto *atual, Ponto *dir, FuncaoErro func_matematica);               

#endif

