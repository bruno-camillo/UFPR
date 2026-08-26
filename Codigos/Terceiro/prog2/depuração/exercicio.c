#include <stdlib.h>
#include <stdio.h>

int main (void){
    int *vector_int, i;
    short *vector_short;

    vector_int = (int*) malloc(10 * sizeof(int));
    vector_short = (short*) malloc(4 * sizeof(short));

    for (i = 0; i < 4; i++){
        vector_int[i] = i;
        vector_short[i] = i;
    }

    for (; i < 14; i++){
        vector_int[i] = i;
    }

    printf("Shorts:[%d] [%d] [%d] [%d]\n", 
           vector_short[0], vector_short[1], 
           vector_short[2], vector_short[3]);

    free(vector_int);
    free(vector_short);

    return 0;
}