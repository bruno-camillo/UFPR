// programa principal do projeto "The Boys - 2024/2"
// Autor: Bruno Bertussi Camillo, GRR 20252947

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"
#include "eventos.h"

// Definição dos tipos de eventos
#define TIPO_CHEGA 1
#define TIPO_ENTRA 2
#define TIPO_SAI 3
#define TIPO_VIAJA 4
#define TIPO_MORRE 5
#define TIPO_MISSAO 6
#define TIPO_ESPERA 7
#define TIPO_DESISTE 8
#define TIPO_AVISA 9
#define TIPO_FIM 10

#define T_INICIO 0
#define T_FIM 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 5
#define N_MISSOES T_FIM / 100
#define N_COMPOSTOS_V  N_HABILIDADES * 3

//programa principal
int main () {
    struct mundo m;
    struct fprio_t *lef = fprio_cria();
    int tipo = -1;
    int prio;
    struct evento *exec;
    struct evento_missao *execMissao;
    void *tipoEvento;
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();

    srand(time(NULL));

    INICIALIZA_MUNDO(&m);
	
    EVENTOS_INICIAIS(&m, lef);

	// executa os eventos ate chegar no evento fim
    while (lef -> prim != NULL && tipo != TIPO_FIM) {
        tipoEvento = fprio_retira(lef, &tipo, &prio);
        m.nEventos++;

		// verifica o tipo, visto que existe o evento e o evento_missao
        if (tipo != TIPO_MISSAO) {
            exec = tipoEvento;
            exec->func(exec->m, exec->T, exec->idHeroi, exec->idBase, exec->lef);
        } else {
                execMissao = tipoEvento;
                execMissao -> func(execMissao->m, execMissao->T, execMissao->idMissao, execMissao->lef);
            }
        free(tipoEvento);

        if (tipo == TIPO_FIM)
            break;
    }

    DESTROI_MUNDO(&m);
    fprio_destroi(lef);

    fim = clock();

    tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("TEMPO TOTAL: %.2f segundos\n", tempo_gasto); // exibe o tempo de execucao

    return 0;
}