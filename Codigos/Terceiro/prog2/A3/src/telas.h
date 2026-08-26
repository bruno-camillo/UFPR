#ifndef TELAS_H
#define TELAS_H

#include "estruturas.h"

void desenha_menu(int botao_selecionado, GerenciadorSprites *sprites);

void desenha_game_over(int botao_selecionado, GerenciadorSprites *sprites);

void desenha_jogo(Jogador *j, 
                  Inimigo inimigos[], int qtd_inimigos, 
                  Plataforma plataformas[], int qtd_plataformas, 
                  ItemMundo itens[], int qtd_itens, 
                  GerenciadorSprites *sprites,
                  float camera_x);

void desenha_pausa(int botao_selecionado, GerenciadorSprites *sprites);

void desenha_vitoria(int botao_selecionado, GerenciadorSprites *sprites);

#endif