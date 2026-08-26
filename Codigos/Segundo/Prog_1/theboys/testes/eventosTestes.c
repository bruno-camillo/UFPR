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

// Função para criar um novo evento
// Missao nao é incluida, pois eventos atuais nao envolvem missao diretamente
// Retorna 1 em caso de sucesso, e 0 caso contrario
int criaEvento (struct evento **e, void (*func)(struct mundo *, int, int, int, struct fprio_t*), struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    if (!e || !lef || !func || !m)
        return 0;
    
    if (!((*e) = malloc(sizeof(struct evento))))
        return 0;

    (*e) -> func = func;
    (*e) -> m = m;
    (*e) -> T = T;
    (*e) -> idHeroi = idHeroi;
    (*e) -> idBase = idBase;
    (*e) -> lef = lef;

    return 1;
}

int criaMissao (struct evento_missao **missao, void (*func)(struct mundo *, int, int, struct fprio_t*), struct mundo *m, int T, int idMissao, struct fprio_t *lef) {
    if (!missao || !lef || !func || !m)
        return 0;

    if (!((*missao) = malloc(sizeof(struct evento_missao))))
        return 0;

    (*missao) -> func = func;
    (*missao) -> m = m;
    (*missao) -> T = T;
    (*missao) -> idMissao = idMissao;
    (*missao) -> lef = lef;

    return 1;
}

// Representa um heroi H chegando em uma base B no instante T. Ao chegar, o
// heroi analisa o tamanho da fila e decide se espera para entrar ou desiste
void CHEGA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    bool espera;
    struct evento *proxEvento;

    if (!lef || !m)
        return;

    //atualiza a base do heroi
    m -> herois[idHeroi].base = idBase;

    // define se heroi espera ou desiste
    if (m -> bases[idBase].pres -> num < m -> bases[idBase].lot && m -> bases[idBase].esp -> num == 0) 
        espera = true;
    else
        espera = (m -> herois[idHeroi].paci > 10 * m -> bases[idBase].esp -> num);

    if (espera) 
    {
        criaEvento(&proxEvento, ESPERA, m, T, idHeroi, idBase, lef);
        fprio_insere(lef, proxEvento, TIPO_ESPERA, T);
        printf ("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", T, idHeroi, idBase, m -> bases[idBase].pres -> num, m -> bases[idBase].lot);
    }
    else    
    {
        criaEvento(&proxEvento, DESISTE, m, T, idHeroi, idBase, lef);
        fprio_insere(lef, proxEvento, TIPO_DESISTE, T);
        printf ("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", T, idHeroi, idBase, m -> bases[idBase].pres -> num, m -> bases[idBase].lot);
    }
}

// O heroi H entra na fila de espera da base B. Assim que H entrar na fila, o
// porteiro da base B deve ser avisado para verificar a fila
void ESPERA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    struct evento *proxEvento;

    if (!lef || !m)
        return;

    fila_insere(m -> bases[idBase].esp, idHeroi);

    criaEvento(&proxEvento, AVISA, m, T, -1, idBase, lef);
    fprio_insere(lef, proxEvento, TIPO_AVISA, T);
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", T, idHeroi, idBase, m -> bases[idBase].esp -> num);
}

// O heroi H desiste de entrar na base B, escolhe uma base aleatoria D e viaja
// para la
void DESISTE (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int D = rand() % m -> nBases;
    struct evento *proxEvento;

    if (!lef || !m)
        return;

    criaEvento(&proxEvento, VIAJA, m, T, idHeroi, D, lef);
    fprio_insere(lef, proxEvento, TIPO_VIAJA, T);
    printf("%6d: DESISTE HEROI %2d BASE %d\n", T, idHeroi, idBase);
}

// O porteiro da base B trata a fila de espera
// idHeroi nao é necessario nesse caso, deve ser -1
void AVISA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int primHeroi;
    struct evento *proxEvento;
    struct cjto_t *aux;

    if (!lef || !m)
        return;

    printf ("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", T, idBase, m -> bases[idBase].pres -> num, m -> bases[idBase].lot);
    fila_imprime(m -> bases[idBase].esp);
    printf(" ]\n");

    while (m -> bases[idBase].pres -> num < m -> bases[idBase].lot && m -> bases[idBase].esp -> num > 0) {
        if (fila_retira(m -> bases[idBase].esp, &primHeroi)) 
        {
            cjto_insere(m -> bases[idBase].pres, primHeroi);
            
            // ponteiro anterior de habilidades eh perdido, SALVAR NUMA VARIAVEL E DAR FREE
            aux = m -> bases[idBase].hab;
            m -> bases[idBase].hab = cjto_uniao(m -> bases[idBase].hab, m -> herois[primHeroi].hab);
            cjto_destroi(aux);
           

            criaEvento(&proxEvento, ENTRA, m, T, primHeroi, idBase, lef);
            fprio_insere(lef, proxEvento, TIPO_ENTRA, T);
            printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", T, idBase, primHeroi);
        }
    }
}

// O heroi H entra na base B. Ao entrar, o heroi decide quanto tempo vai ficar e
// agenda sua saıda da base
void ENTRA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int TPB; // tempo de permanencia na base
    struct evento *proxEvento;

    if (!lef || !m)
        return;

    TPB = 15 + m -> herois[idHeroi].paci * (rand() % (20 + 1));

    if (T + TPB < T_FIM) {
        criaEvento(&proxEvento, SAI, m, T + TPB, idHeroi, idBase, lef);
        fprio_insere(lef, proxEvento, TIPO_SAI, T + TPB);

        printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", T, idHeroi, idBase, m -> bases[idBase].pres -> num, m -> bases[idBase].lot, T + TPB);
    }
}

// O heroi H sai da base B. Ao sair, escolhe uma base de destino para viajar; o
// porteiro de B e avisado, pois uma vaga foi liberada
void SAI (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int D = rand() % m -> nBases;
    struct evento *proxEvento;
    struct cjto_t *aux;

    if (!lef || !m)
        return;

    //retira o heroi da base e reicinia o conjuntos de habilidades da base
    cjto_retira(m -> bases[idBase].pres, idHeroi);
    aux = m -> bases[idBase].hab;
    m -> bases[idBase].hab = cjto_cria(m -> nHab);
    cjto_destroi(aux);

    // recalcula as habilidades presentes na base
    for (int i = 0; i < m -> nHerois; i++) 
        if (cjto_pertence(m -> bases[idBase].pres, i)) {
            aux = m -> bases[idBase].hab;
            m -> bases[idBase].hab = cjto_uniao (m -> bases[idBase].hab, m -> herois[i].hab);
            cjto_destroi(aux);
        }

    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", T, idHeroi, idBase, m -> bases[idBase].pres -> num, m -> bases[idBase].lot);

    criaEvento(&proxEvento, AVISA, m, T, idHeroi, idBase, lef);
    fprio_insere(lef, proxEvento, TIPO_AVISA, T);

    criaEvento(&proxEvento, VIAJA, m, T, idHeroi, D, lef);
    fprio_insere(lef, proxEvento, TIPO_VIAJA, T);
}

// O heroi H se desloca para uma base D (que pode ser a mesma onde ja esta)
// Calcula a duracao da viagem com base na distancia entre as bases e a velocidade do heroi
void VIAJA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int distX, distY, dist, duracao;
    struct evento *proxEvento;

    if(!lef || !m)
        return;

    distX = abs(m -> bases[idBase].local.x - m -> bases[m -> herois[idHeroi].base].local.x);
    distY = abs(m -> bases[idBase].local.y - m -> bases[m -> herois[idHeroi].base].local.y);

    dist = abs(sqrt(distX * distX + distY * distY));

    duracao = abs(dist) / m -> herois[idHeroi].vel;

    if (T + duracao < T_FIM) {
        criaEvento(&proxEvento, CHEGA, m, (T + duracao), idHeroi, idBase, lef);
        fprio_insere(lef, proxEvento, TIPO_CHEGA, T + duracao);

        printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", 
            T, idHeroi, m -> herois[idHeroi].base, idBase, dist, m -> herois[idHeroi].vel, T + duracao);
    }
}

// O heroi H morre no instante T
void MORRE (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    struct evento *proxEvento;

    if(!lef || !m)
        return;

    if (m -> herois[idHeroi].status == 0)
        return;

    //retira o heroi da base e reicinia o conjuntos de habilidades da base
    cjto_retira(m -> bases[idBase].pres, idHeroi);
    cjto_destroi(m -> bases[idBase].hab);
    m -> bases[idBase].hab = cjto_cria(m -> nHab);

    // recalcula as habilidades presentes na base
    for (int i = 0; i < m -> nHerois; i++) 
        if (cjto_pertence(m -> bases[idBase].pres, i))
            m -> bases[idBase].hab = cjto_uniao (m -> bases[idBase].hab, m -> herois[i].hab);

    m -> herois[idHeroi].status = 0; // atualiza status do heroi para morto

    criaEvento(&proxEvento, AVISA, m, T, idHeroi, idBase, lef);
    fprio_insere(lef, proxEvento, TIPO_AVISA, T);

    printf("%6d: MORRE HEROI %2d MISSAO %d\n", T, idHeroi, m -> bases[idBase].missaoCompV); 

    m -> heroisMortos++;
}

void MISSAO (struct mundo *m, int T, int idMissao, struct fprio_t *lef) {
    int i, BMP, distanciaMissao, menorDist, distX, distY, baseCompV;
    struct evento_missao *proxEvento_missao;
    struct evento *proxEvento;

    if(!lef || !m)
        return;

    // calcula a maior distancia da missao possivel
    menorDist = abs(m -> tamMundo.x * 1.41 + 1); 

    // inicializa a base mais proxima e a base que podera usar o composto V
    BMP = -1;
    baseCompV = -1;

    // calcula a distancia de cada base até a missão
    for (i = 0; i < m -> nBases; i++) {
        distX = abs(m -> missoes[idMissao].local.x - m -> bases[i].local.x);
        distY = abs(m -> missoes[idMissao].local.y - m -> bases[i].local.y);  

        distanciaMissao = abs(sqrt(distX * distX + distY * distY));

        // define se a base eh a mais proxima, caso contenha as habilidades necessarias
        if (distanciaMissao < menorDist && cjto_contem(m -> bases[i].hab, m -> missoes[idMissao].hab)) {
            BMP = distanciaMissao;
            BMP = i;
        }

        // define a base mais proxima para o uso do composto V
        if (m -> bases[i].pres -> num > 0 && distanciaMissao < menorDist)
            baseCompV = i;
    }

    // declaracao de novas variaveis para condicional baseada na BMP
    int heroisBase[N_HEROIS];
    int tam = 0, k, maisExp, aux;

    m -> missoes[idMissao].tentativa++;

    if (m -> missoes[idMissao].tentativa < m -> tentativaMin)
        m -> tentativaMin = m -> missoes[idMissao].tentativa;
      
    if (m -> missoes[idMissao].tentativa > m -> tentativaMax)
        m -> tentativaMax = m -> missoes[idMissao].tentativa;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", T, idMissao, m -> missoes[idMissao].tentativa);
    cjto_imprime(m -> missoes[idMissao].hab);
    printf(" ]\n");

    // se alguma base tiver as habilidades necessarias, a missao eh dada como cumprida
    // e a experiencia dos herois aumentada
    if (BMP != -1) {
            m -> missoes[idMissao].cumprida = 1;
        
            // define um vetor dos ids dos herois presentes nas bases
            for (int i = 0; i < m -> nHerois; i++) 
                if (cjto_pertence(m -> bases[BMP].pres, i)){
                    heroisBase[tam] = m -> herois[i].id;
                    tam++;
                }

            for (k = 0; k < tam; k++)
                    m -> herois[heroisBase[k]].xp++;

            printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", T, idMissao, BMP);
            cjto_imprime(m -> missoes[idMissao].hab);
            printf(" ]\n");

            m -> bases[BMP].participaMissao++;
            m -> missoesCumpridas++;
            m -> somaTentativas += m -> missoes[idMissao].tentativa;
            m -> mediaTentativa = (double)m -> somaTentativas / m -> missoesCumpridas;
    }
    // caso contrario, podera ser usado um compostoV, caso tenham os requisitos
    // T deve ser multiplo de 2500, e devem ter compostoV disponivel no mundo
    else {
            if (m -> nCompostosV > 0 && T % 2500 == 0) {
                m -> nCompostosV = m -> nCompostosV - 1;
                m -> missoes[idMissao].cumprida = 1;

                // define um vetor dos ids dos herois presentes nas bases
                for (int i = 0; i < m -> nHerois; i++) 
                    if (cjto_pertence(m -> bases[baseCompV].pres, i)){
                        heroisBase[tam] = m -> herois[i].id;
                        tam++;
                    }

                maisExp = 0;
                for (k = 1; k < tam; k++)
                    if (m -> herois[maisExp].xp < m -> herois[heroisBase[k]].xp)
                        maisExp = heroisBase[k];

                m -> bases[baseCompV].missaoCompV = idMissao;

                criaEvento(&proxEvento, MORRE, m, T, maisExp, baseCompV, lef);
                fprio_insere(lef, proxEvento, TIPO_MORRE, T);

                // troca de posicao do heroi com mais xp com o ultimo herois, para "remove-lo" do vetor
                aux = heroisBase[maisExp];
                heroisBase[maisExp] = heroisBase[tam - 1];
                heroisBase[tam - 1] = aux;
                tam--;

                // incrementa xp para os herois restantes
                for (k = 0; k < tam; k++)
                    m -> herois[heroisBase[k]].xp++;

                printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", T, idMissao, baseCompV);
                cjto_imprime(m -> missoes[idMissao].hab);
                printf(" ]\n");
                m -> bases[baseCompV].participaMissao++;
                m -> missoesCumpridas++;
                m -> somaTentativas += m -> missoes[idMissao].tentativa;
                m -> mediaTentativa = (double)m -> somaTentativas / m -> missoesCumpridas;
            } 
            // caso contrario, a missao eh passada para o dia seguinte
            else {
                criaMissao(&proxEvento_missao, MISSAO, m, T + 24*60, idMissao, lef);
                fprio_insere(lef, proxEvento_missao, TIPO_MISSAO, T + 24*60);

                printf("%6d: MISSAO %d IMPOSSIVEL\n", T, idMissao);
            }
        }
}

// Encerra a simulacao no instante T
void FIM (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int i, totalMissoes = N_MISSOES, totalHerois = N_HEROIS;
    printf("%d: FIM\n", T);

    for (i = 0; i < m -> nHerois; i++) {
        if (m -> herois[i].status == 1) 
        {
            printf("HEROI %d  VIVO  PAC %d  VEL %d  EXP %d  HABS [ ",
                m -> herois[i].id, m -> herois[i].paci, m -> herois[i].vel, m -> herois[i].xp );
            cjto_imprime(m -> herois[i].hab);
            printf(" ]\n");
        } 
        else 
        {
            printf("HEROI %d  MORTO  PAC %d  VEL %d  EXP %d  HABS [ ",
                m -> herois[i].id, m -> herois[i].paci, m -> herois[i].vel, m -> herois[i].xp);
            cjto_imprime(m -> herois[i].hab);
            printf(" ]\n");
        }
    }

    for (i = 0; i < m -> nBases; i++) 
        printf ("BASE %d  LOT %d FILA MAX %d MISSOES %d\n",
            m -> bases[i].id, m -> bases[i].lot, m -> bases[i].esp -> num, m -> bases[i].participaMissao);
    
    printf("EVENTOS TRATADOS: %d\n", m -> nEventos);

    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", m -> missoesCumpridas, N_MISSOES, ((double)m->missoesCumpridas / totalMissoes) * 100);

    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", m -> tentativaMin, m -> tentativaMax, m -> mediaTentativa);

    printf("TAXA MORTALIDADE: %.1f%%\n", ((double)m -> heroisMortos / totalHerois) * 100);
}

// inicializacao do mundo virtual
void INICIALIZA_MUNDO (struct mundo *m) {
    int i;

    m -> nHerois = N_HEROIS;
    m -> herois = malloc(N_HEROIS * sizeof(struct heroi));
    m -> nBases = N_BASES;
    m -> bases = malloc(N_BASES * sizeof(struct base));
    m -> nMissoes = N_MISSOES;
    m -> missoes = malloc(N_MISSOES * sizeof(struct missao));
    m -> nHab = N_HABILIDADES;
    m -> nCompostosV = N_COMPOSTOS_V;
    m -> tamMundo.x = N_TAMANHO_MUNDO;
    m -> tamMundo.y = N_TAMANHO_MUNDO;
    m -> relogio = T_INICIO;
    m -> mediaTentativa = 0;
    m -> tentativaMax = 0;
    m -> tentativaMin = 1000;
    m -> heroisMortos = 0;
    m -> missoesCumpridas = 0;
    m -> nEventos = 0;
    m -> somaTentativas = 0;

    // inicializa herois
    for (i = 0; i < N_HEROIS; i++) {
        m -> herois[i].id = i;
        m -> herois[i].hab = cjto_cria(N_HABILIDADES);
        while (cjto_card(m -> herois[i].hab) < 3) 
            cjto_insere(m->herois[i].hab, rand() % N_HABILIDADES); // recebe 3 habilidades aleatorias em um conjunto
        m -> herois[i].paci = rand() % (100 - 0 + 1); // numero aleatorio entre 0 e 100
        m -> herois[i].vel = 50 + (rand() % (5000 - 50 + 1)); // numero aleatorio entre 50 e 5000
        m -> herois[i].xp = 0;
        m -> herois[i].base = -1; // -1 indica que o heroi nao esta em nenhuma base
        m -> herois[i].status = 1; // 1 indica que o heroi esta vivo
    }

    // inicializa bases
    for (i = 0; i < N_BASES; i++) {
        m -> bases[i].id = i;
        m -> bases[i].lot = 3 + (rand() % (10 - 3 + 1)); // lotacao entre 3 e 10
        m -> bases[i].pres = cjto_cria(N_HEROIS);
        m -> bases[i].esp = fila_cria();
        m -> bases[i].local.x = rand() % N_TAMANHO_MUNDO;
        m -> bases[i].local.y = rand() % N_TAMANHO_MUNDO;   
        m -> bases[i].missaoCompV = -1;
        m -> bases[i].participaMissao = 0;
        m -> bases[i].hab = cjto_cria(N_HABILIDADES);
    }

    // inicializa missoes
    for (i = 0; i < N_MISSOES; i++) {
        m -> missoes[i].id = i;
        m -> missoes[i].hab = cjto_cria(N_HABILIDADES);
        int maxHabs = 6 + rand() % (10 - 6 + 1);
        while (cjto_card(m -> missoes[i].hab) < maxHabs) {
            fprintf(stderr,"aqui");
            cjto_insere(m -> missoes[i].hab, rand() % N_HABILIDADES); // recebe de 6 a 10 habilidades aleatorias em um conjunto
        }
        m -> missoes[i].cumprida = 0;
        m -> missoes[i].tentativa = 0;
        m -> missoes[i].local.x = rand() % N_TAMANHO_MUNDO;
        m -> missoes[i].local.y = rand() % N_TAMANHO_MUNDO;   
    }
}

void DESTROI_MUNDO (struct mundo *m) {
    int i;

    for (i = 0; i < N_HEROIS; i++)
        cjto_destroi(m -> herois[i].hab);

    for (i = 0; i < N_BASES; i++) {
        cjto_destroi(m -> bases[i].pres);
        cjto_destroi(m -> bases[i]. hab);
        fila_destroi(m -> bases[i].esp);
    }

    for (i = 0; i < N_MISSOES; i++)
        cjto_destroi(m -> missoes[i].hab);

    free(m->herois);
    free(m->bases);
    free(m->missoes);    
}

void EVENTOS_INICIAIS (struct mundo *m, struct fprio_t *lef) {
    int i, tempoMissao;
    struct evento *proxEvento;
    struct evento_missao *proxMissao;

    if (!lef)   
        return;

    // agenda a chegada de todos os herois no instante T_INICIO
    for (i = 0; i < m -> nHerois; i++) {
        criaEvento(&proxEvento, CHEGA, m, rand() % 4321, i, rand() % m -> nBases, lef);
        fprio_insere(lef, proxEvento, TIPO_CHEGA, T_INICIO);
    }

    for (i = 0; i < m -> nMissoes; i++) {
        tempoMissao = T_INICIO + (rand() % T_FIM); // numero aleatorio entre o T_INICIO e T_FIM
        criaMissao(&proxMissao, MISSAO, m, tempoMissao, i, lef);
        
        fprio_insere(lef, proxMissao, TIPO_MISSAO, tempoMissao);
        }

    criaEvento(&proxEvento, FIM, m, T_FIM, -1, -1, lef);
    fprio_insere(lef, proxEvento, TIPO_FIM, T_FIM);
}

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

    while (lef -> prim != NULL && tipo != TIPO_FIM) {
        tipoEvento = fprio_retira(lef, &tipo, &prio);
        m.nEventos++;

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
    printf("TEMPO TOTAL: %.2f minutos\n", tempo_gasto / 60);

    return 0;
}