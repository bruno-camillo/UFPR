#include <stdio.h>
#include "mapa.h"

// Função para carregar os dados do mundo a partir de arquivos
// Esta função lê os arquivos "mapa.txt", "inimigos.txt" e "itens.txt" 
// para inicializar as plataformas, inimigos e itens no mundo do jogo.
void carregar_dados_mundo(Plataforma lista_plat[], int *qtd_plat, 
                          Inimigo lista_inim[], int *qtd_inim,
                          ItemMundo lista_itens[], int *qtd_itens) {
    
    // Zerando as contagens antes de iniciar a leitura dos arquivos
    *qtd_plat = 0;
    *qtd_inim = 0;
    *qtd_itens = 0;

    // Carregar a lista de plataformas do mundo
    FILE *arq_mapa = fopen("mapa.txt", "r");
    int i = 0;
    if (arq_mapa != NULL) {
        while (i < MAX_PLATAFORMAS && fscanf(arq_mapa, "%f %f %f %f %d", 
               &lista_plat[i].x, &lista_plat[i].y, 
               &lista_plat[i].largura, &lista_plat[i].altura, 
               &lista_plat[i].comportamento) != EOF) {
            
            lista_plat[i].ativa = true;
            lista_plat[i].direcao = (i % 2 == 0) ? 1.0f : -1.0f;
            // Se a plataforma for móvel, define os limites de movimento com base no tipo de comportamento
            if (lista_plat[i].comportamento == PLAT_MOVEL_VERT) {
                lista_plat[i].limite_min = lista_plat[i].y - 300.0f; 
                lista_plat[i].limite_max = lista_plat[i].y + 100.0f;
            }
            // Se a plataforma for móvel horizontal, define os limites de movimento
            else if (lista_plat[i].comportamento == PLAT_MOVEL_HORIZ) {
                lista_plat[i].limite_min = lista_plat[i].x - 200.0f; 
                lista_plat[i].limite_max = lista_plat[i].x + 250.0f; 
            }
            i++;
        }
        fclose(arq_mapa);
    }
    *qtd_plat = i;

    // Carregar a lista de inimigos do mundo
    FILE *arq_inim = fopen("inimigos.txt", "r");
    int j = 0;
    if (arq_inim != NULL) {
        while (j < MAX_INIMIGOS && fscanf(arq_inim, "%f %f %d %d %d", 
               &lista_inim[j].x, &lista_inim[j].y, 
               &lista_inim[j].largura, &lista_inim[j].altura, 
               &lista_inim[j].tipo) != EOF) {
            
            lista_inim[j].ativo = true;
            lista_inim[j].vy = 0.0f;
            lista_inim[j].vida = 20;  

            // Define a velocidade horizontal com base no tipo de inimigo
            if (lista_inim[j].tipo != 0) {
                lista_inim[j].vx = -2.5f; 
            } else {
                lista_inim[j].vx = -1.5f; 
            }

            j++;
        }
        fclose(arq_inim);
    }
    *qtd_inim = j;

    // Carregar a lista de itens do mundo
    FILE *arq_itens = fopen("itens.txt", "r");
    int k = 0;
    if (arq_itens != NULL) {
        while (k < MAX_ITENS && fscanf(arq_itens, "%f %f %f %f %d", 
               &lista_itens[k].x, &lista_itens[k].y, 
               &lista_itens[k].largura, &lista_itens[k].altura, 
               &lista_itens[k].tipo) != EOF) {
            
            lista_itens[k].ativo = true;
            k++;
        }
        fclose(arq_itens);
    }
    *qtd_itens = k;
}

// Atualiza o movimento independente das plataformas moveis a cada frame
void atualizar_plataformas_moveis(Plataforma lista_plat[], int qtd_plat) {
    for (int i = 0; i < qtd_plat; i++) {
        if (!lista_plat[i].ativa) continue;

        // Atualiza a posição da plataforma com base no seu comportamento
        if (lista_plat[i].comportamento == PLAT_MOVEL_VERT) {
            lista_plat[i].y += (1.5f * lista_plat[i].direcao);
            if (lista_plat[i].y <= lista_plat[i].limite_min || lista_plat[i].y >= lista_plat[i].limite_max) {
                lista_plat[i].direcao *= -1.0f; 
            }
        }
        // Atualiza a posição da plataforma horizontalmente se for do tipo PLAT_MOVEL_HORIZ
        else if (lista_plat[i].comportamento == PLAT_MOVEL_HORIZ) {
            lista_plat[i].x += (2.0f * lista_plat[i].direcao);
            if (lista_plat[i].x <= lista_plat[i].limite_min || lista_plat[i].x >= lista_plat[i].limite_max) {
                lista_plat[i].direcao *= -1.0f; 
            }
        }
    }
}