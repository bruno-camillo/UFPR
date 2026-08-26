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

    // define a=qual evento sera adicionado na lef
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

void ESPERA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    struct evento *proxEvento;

    if (!lef || !m)
        return;

    // insere heroi na lista de espera
    fila_insere(m -> bases[idBase].esp, idHeroi);

    criaEvento(&proxEvento, AVISA, m, T, -1, idBase, lef);
    fprio_insere(lef, proxEvento, TIPO_AVISA, T);
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", T, idHeroi, idBase, m -> bases[idBase].esp -> num);
}

void DESISTE (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int D = rand() % m -> nBases; // define qual sera o destino do heroi, aleatoriamente
    struct evento *proxEvento;

    if (!lef || !m)
        return;

    criaEvento(&proxEvento, VIAJA, m, T, idHeroi, D, lef);
    fprio_insere(lef, proxEvento, TIPO_VIAJA, T);
    printf("%6d: DESISTE HEROI %2d BASE %d\n", T, idHeroi, idBase);
}

void AVISA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int primHeroi;
    struct evento *proxEvento;
    struct cjto_t *aux;

    if (!lef || !m)
        return;

    (void)idHeroi; //marcando como inutilizado

    printf ("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", T, idBase, m -> bases[idBase].pres -> num, m -> bases[idBase].lot);
    fila_imprime(m -> bases[idBase].esp);
    printf(" ]\n");

    // se a base nao estiver lotada e estiver alguem na fila, o porteiro libera a entrada do primeiro heroi da fila
    // e o insere no conjunto de herois presentes na base
    // o conjunto de habilidades da base eh atualizado
    while (m -> bases[idBase].pres -> num < m -> bases[idBase].lot && m -> bases[idBase].esp -> num > 0) {
        if (fila_retira(m -> bases[idBase].esp, &primHeroi)) 
        {
            cjto_insere(m -> bases[idBase].pres, primHeroi);
            
            aux = m -> bases[idBase].hab;
            m -> bases[idBase].hab = cjto_uniao(m -> bases[idBase].hab, m -> herois[primHeroi].hab); // atualizando habilidades
            cjto_destroi(aux);
           

            criaEvento(&proxEvento, ENTRA, m, T, primHeroi, idBase, lef);
            fprio_insere(lef, proxEvento, TIPO_ENTRA, T);
            printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", T, idBase, primHeroi);
        }
    }
}

void ENTRA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int TPB; // tempo de permanencia na base
    struct evento *proxEvento;

    if (!lef || !m)
        return;

    // define o tempo de permanencia baseado na paciencia do heroi
    TPB = 15 + m -> herois[idHeroi].paci * (rand() % (20 + 1));

    // verifica se ele vai sair antes do tempo de fim do mundo
    if (T + TPB < T_FIM) {
        criaEvento(&proxEvento, SAI, m, T + TPB, idHeroi, idBase, lef);
        fprio_insere(lef, proxEvento, TIPO_SAI, T + TPB);

        printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", T, idHeroi, idBase, m -> bases[idBase].pres -> num, m -> bases[idBase].lot, T + TPB);
    }
}

void SAI (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int D = rand() % m -> nBases; // define um destino aleatoriamente
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

void VIAJA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    int distX, distY, dist, duracao;
    struct evento *proxEvento;

    if(!lef || !m)
        return;

    // calculo da distancia cartesiana da base atual ate a proxima
    distX = abs(m -> bases[idBase].local.x - m -> bases[m -> herois[idHeroi].base].local.x);
    distY = abs(m -> bases[idBase].local.y - m -> bases[m -> herois[idHeroi].base].local.y);

    dist = fabs(sqrt(distX * distX + distY * distY));

    duracao = abs(dist / m -> herois[idHeroi].vel);

    // verifica se o heroi chega na base antes do fim
    // caso contrario ele nem viaja
    if (T + duracao < T_FIM) {
        criaEvento(&proxEvento, CHEGA, m, (T + duracao), idHeroi, idBase, lef);
        fprio_insere(lef, proxEvento, TIPO_CHEGA, T + duracao);

        printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", 
            T, idHeroi, m -> herois[idHeroi].base, idBase, dist, m -> herois[idHeroi].vel, T + duracao);
    }
}

void MORRE (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef) {
    struct evento *proxEvento;
    struct cjto_t *aux;

    if(!lef || !m)
        return;

    // verifica se o heroi ja nao esta morto
    if (m -> herois[idHeroi].status == 0)
        return;

    // retira o heroi da base e reicinia o conjuntos de habilidades da base
    cjto_retira(m -> bases[idBase].pres, idHeroi);
    cjto_destroi(m -> bases[idBase].hab);
    m -> bases[idBase].hab = cjto_cria(m -> nHab);

    // recalcula as habilidades presentes na base
    for (int i = 0; i < m -> nHerois; i++) 
        if (cjto_pertence(m -> bases[idBase].pres, i)) {
            aux = m -> bases[idBase].hab;
            m -> bases[idBase].hab = cjto_uniao (m -> bases[idBase].hab, m -> herois[i].hab);
            cjto_destroi(aux);
        }

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
    menorDist = fabs(m -> tamMundo.x * 1.41 + 1); 

    // inicializa a base mais proxima e a base que podera usar o composto V
    BMP = -1;
    baseCompV = -1;

    // calcula a distancia cartesiana de cada base até a missão
    for (i = 0; i < m -> nBases; i++) {
        distX = abs(m -> missoes[idMissao].local.x - m -> bases[i].local.x);
        distY = abs(m -> missoes[idMissao].local.y - m -> bases[i].local.y);  

        distanciaMissao = fabs(sqrt(distX * distX + distY * distY));

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

    // define se o numero de tentativas da missao eh a menor entre as missoes
    if (m -> missoes[idMissao].tentativa < m -> tentativaMin)
        m -> tentativaMin = m -> missoes[idMissao].tentativa;
      
    // define se o numero de tentativas da missao eh a maior entre as missoes
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

            // incrementa xp aos herois da base que estao vivos
            for (k = 0; k < tam; k++)
                if (m -> herois[heroisBase[k]].status == 1)
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
                // busca o indice do heroi com mais xp
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

                // incrementa xp para os herois que estao vivos
                for (k = 0; k < tam; k++)
                    if (m -> herois[heroisBase[k]].status == 1)
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
    
    // marcando como inutilizado
    (void) idHeroi;
    (void) idBase;
    (void) lef;

    printf("%d: FIM\n", T);

    // define os status de cada heroi
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

    // define os status de cada base
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
    int i, k, maxHabs;
    int baralho[N_HABILIDADES];

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
        maxHabs = 6 + rand() % (10 - 6 + 1); 
        
        // define um vetor com todas as habilidades possiveis
        for (k = 0; k < N_HABILIDADES; k++) {
            baralho[k] = k;
        }

        // embaralhar o vetor (troca posições aleatoriamente)
        for (k = 0; k < N_HABILIDADES; k++) {
            int r = rand() % N_HABILIDADES;
            int temp = baralho[k];
            baralho[k] = baralho[r];
            baralho[r] = temp;
        }

        // pegar as primeiras 'maxHabs' cartas do baralho embaralhado
        for (k = 0; k < maxHabs; k++) {
            cjto_insere(m->missoes[i].hab, baralho[k]);
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

    // define o instante que as missoes vao acontecer
    for (i = 0; i < m -> nMissoes; i++) {
        tempoMissao = T_INICIO + (rand() % T_FIM); // numero aleatorio entre o T_INICIO e T_FIM
        criaMissao(&proxMissao, MISSAO, m, tempoMissao, i, lef);
        
        fprio_insere(lef, proxMissao, TIPO_MISSAO, tempoMissao);
        }

    criaEvento(&proxEvento, FIM, m, T_FIM, -1, -1, lef);
    fprio_insere(lef, proxEvento, TIPO_FIM, T_FIM);
}