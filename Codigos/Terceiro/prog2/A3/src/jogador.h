#ifndef JOGADOR_H
#define JOGADOR_H

#include "estruturas.h"

void inicializar_jogador(Jogador *j);

void atualizar_jogador(Jogador *j, Plataforma plataformas[], int qtd_plataformas, bool tecla_baixo);

int checar_coleta_itens(Jogador *j, ItemMundo itens[], int qtd_itens);

void processar_dano_jogador(Jogador *j, Inimigo inimigos[], int qtd_inimigos, ItemMundo itens[], int qtd_itens);

#endif