/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>


/* programa principal */
int main ()
{
    srand (0); /* use assim, com zero */
    
    int n, max, min;
    scanf ("%d %d", &n, &max);
    min = -max;          
    
    struct racional r1, r2;
    imprime_operacoes (n, min, max, r1, r2);

    return (0) ;
}
