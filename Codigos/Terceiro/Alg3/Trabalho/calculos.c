#include "calculos.h"

float area_triangulo(float x1, float y1,
                     float x2, float y2,
                     float x3, float y3) {
    float area;

    area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
    return (area < 0.0) ? -area : area;
}


float altura2_triangulo(float x1, float y1,
                        float x2, float y2,
                        float x3, float y3) {
    float area, dx, dy;

    area = area_triangulo(x1, y1, x2, y2, x3, y3);
    dx = x3 - x1;
    dy = y3 - y1;    
    return 4 * (area * area) / (dx * dx + dy * dy);
}

float calcular_erro(Ponto *esq, Ponto *atual, Ponto *dir, FuncaoErro func_matematica) {
    
    // Executa a função de cálculo recebida nos parâmetros
    return func_matematica(esq->x, esq->y, 
                           atual->x, atual->y, 
                           dir->x, dir->y);
}