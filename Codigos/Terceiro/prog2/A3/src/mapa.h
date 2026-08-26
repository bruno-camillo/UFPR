#ifndef MAPA_H
#define MAPA_H

#include "estruturas.h"

void carregar_dados_mundo(Plataforma lista_plat[], int *qtd_plat, 
                          Inimigo lista_inim[], int *qtd_inim,
                          ItemMundo lista_itens[], int *qtd_itens);

void atualizar_plataformas_moveis(Plataforma lista_plat[], int qtd_plat);

#endif