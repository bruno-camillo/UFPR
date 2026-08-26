#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "calculos.h"


int main(int argc, char *argv[]) {
    // Ponteiro de funcao que guarda o tipo de calculo que o usuario digitou
    FuncaoErro metrica_calculo;

    if (strcmp(argv[1], "-a") == 0) 
        metrica_calculo = area_triangulo; 
    else 
        metrica_calculo = altura2_triangulo; 
    



    return 0;
}