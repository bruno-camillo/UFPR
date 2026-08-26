#include "jogador.h"

// Função para inicializar os atributos do jogador
void inicializar_jogador(Jogador *j) {
    j->x = 250.0f; 
    j->y = 500.0f;
    j->vx = 0.0f;
    j->vy = 0.0f;
    j->largura = 50;
    j->altura = 100; 
    j->vida = 3;     
    j->no_chao = false;
    j->agachado = false; 
    j->invulneravel_timer = 0; 
    j->escalando = false;

    j->pulo_duplo_liberado = false; 
    j->pulos_restantes = 1;
    j->pode_cuspir = false;

    j->stamina = 100.0f; 
    j->executando_dash = false;
    j->tempo_dash_restante = 0;
    j->cooldown_dash = 0;
    j->direcao_dash_x = 1.0f; 
}

// Função para atualizar a posição e o estado do jogador
// Esta função aplica a gravidade, verifica colisões com plataformas e itens, e implementa a lógica de movimento do jogador.
void atualizar_jogador(Jogador *j, Plataforma plataformas[], int qtd_plataformas, bool tecla_baixo) {
    // Atualização do cooldown do dash
    if (j->cooldown_dash > 0) j->cooldown_dash--;

    // Regeneração de Stamina
    if (!j->executando_dash && j->stamina < 100.0f) j->stamina += 0.5f; 

    // Verificação de teto acima do jogador quando agachado
    bool teto_acima = false;
    if (j->agachado) {
        float topo_em_pe_y = j->y - 50.0f;
        for (int i = 0; i < qtd_plataformas; i++) {
            if (!plataformas[i].ativa) continue;
            if (j->x + j->largura > plataformas[i].x && j->x < plataformas[i].x + plataformas[i].largura &&
                topo_em_pe_y + 100 > plataformas[i].y && topo_em_pe_y < plataformas[i].y + plataformas[i].altura) {
                teto_acima = true;
                break;
            }
        }
    }

    // Lógica de agachamento: se a tecla para baixo estiver pressionada e o jogador estiver no chão, ele se agacha
    // caso contrário, ele volta à posição normal.
    if (tecla_baixo && j->no_chao && !j->executando_dash && !j->escalando) {
        if (!j->agachado) {
            j->agachado = true;
            j->altura = 50;   
            j->y += 50.0f;    
        }
    } else if (!tecla_baixo && !teto_acima && j->agachado) {
        j->agachado = false;
        j->altura = 100;  
        j->y -= 50.0f;    
    }

    // Limitação da velocidade horizontal quando agachado
    if (j->agachado && !j->executando_dash) {
        if (j->vx > 2.0f)  j->vx = 2.0f;
        if (j->vx < -2.0f) j->vx = -2.0f;
    }

    bool encostado_na_esquerda = false;
    bool encostado_na_direita = false;

    // Verificação de escalada: se o jogador estiver encostado em uma parede e não estiver no chão, ele pode escalar
    for (int i = 0; i < qtd_plataformas; i++) {
        if (!plataformas[i].ativa || plataformas[i].comportamento != 0) continue; 

        if (j->y + j->altura > plataformas[i].y && j->y < plataformas[i].y + plataformas[i].altura) {
            if (j->x + j->largura >= plataformas[i].x - 2.0f && j->x + j->largura <= plataformas[i].x + 5.0f) {
                encostado_na_direita = true;
            }
            if (j->x <= plataformas[i].x + plataformas[i].largura + 2.0f && j->x >= plataformas[i].x + plataformas[i].largura - 5.0f) {
                encostado_na_esquerda = true;
            }
        }
    }

    // Se o jogador não estiver no chão, estiver encostado em uma parede e 
    // não estiver executando um dash, ele entra no estado de escalada.
    if (!j->no_chao && (encostado_na_esquerda || encostado_na_direita) && !j->executando_dash) {
        if (!j->escalando) {
            j->escalando = true;
            j->vy = 0.8f;
            j->vx = 0.0f;
        }
    } else {
        j->escalando = false;
    }

    // Aplicação da gravidade e lógica de movimento do jogador
    if (j->escalando) {
        j->vy = 0.8f; 
        j->vx = 0.0f; 
        j->pulos_restantes = 0; 
    } 
    else if (j->executando_dash) {
        j->vy = 0.0f; 
        j->vx = j->direcao_dash_x * 12.0f; 
        j->tempo_dash_restante--;
        if (j->tempo_dash_restante <= 0) {
            j->executando_dash = false;
            j->vx = 0.0f;
        }
    } else {
        j->vy += 0.5f; 
    }

    // Atualização da direção do dash com base na velocidade horizontal do jogador
    if (j->vx > 0.0f && !j->executando_dash) j->direcao_dash_x = 1.0f;
    if (j->vx < 0.0f && !j->executando_dash) j->direcao_dash_x = -1.0f;

    int indice_plataforma_pousado = -1;

    // Verificação de colisão com plataformas e ajuste da posição do jogador
    for (int i = 0; i < qtd_plataformas; i++) {
        if (!plataformas[i].ativa) continue;

        // Verifica se o jogador está pousado em cima da plataforma
        if (j->x + j->largura > plataformas[i].x && j->x < plataformas[i].x + plataformas[i].largura) {
            float diferenca_y = (j->y + j->altura) - plataformas[i].y;
            
            // Se a diferença vertical entre o jogador e a plataforma for pequena, 
            // considera-se que o jogador está pousado na plataforma
            if (diferenca_y >= -1.5f && diferenca_y <= 1.5f) {
                indice_plataforma_pousado = i; 
                
                if (plataformas[i].comportamento == 1 && !j->executando_dash) {
                    j->y += (1.5f * plataformas[i].direcao);
                }
                else if (plataformas[i].comportamento == 2 && !j->executando_dash) {
                    j->x += (2.0f * plataformas[i].direcao);
                }
            }
        }
    }

    // Movimentação do jogador e verificação de colisão com plataformas
    // Se o jogador não estiver escalando, ele se move horizontalmente e verifica colisões com plataformas.
    if (!j->escalando) {
        j->x += j->vx;
        for (int i = 0; i < qtd_plataformas; i++) {
            if (!plataformas[i].ativa || i == indice_plataforma_pousado) continue;

            // Verifica se o jogador colidiu com a plataforma no eixo X
            if (j->x + j->largura > plataformas[i].x && j->x < plataformas[i].x + plataformas[i].largura &&
                j->y + j->altura > plataformas[i].y && j->y < plataformas[i].y + plataformas[i].altura) {
                
                if (j->vx > 0.0f)       j->x = plataformas[i].x - j->largura;
                else if (j->vx < 0.0f)  j->x = plataformas[i].x + plataformas[i].largura;

                // Se o jogador estava executando um dash, ele é interrompido ao colidir com a plataforma
                if (j->executando_dash) {
                    j->executando_dash = false;
                    j->tempo_dash_restante = 0;
                }
            }
        }
    }

    // Atualização da posição vertical do jogador e verificação de colisão com plataformas
    j->y += j->vy;
    if (!j->escalando) {
        j->no_chao = false;
        for (int i = 0; i < qtd_plataformas; i++) {
            if (!plataformas[i].ativa) continue;
            // Verifica se o jogador colidiu com a plataforma no eixo Y
            if (j->x + j->largura > plataformas[i].x && j->x < plataformas[i].x + plataformas[i].largura &&
                j->y + j->altura > plataformas[i].y && j->y < plataformas[i].y + plataformas[i].altura) {
                // Ajusta a posição do jogador para evitar sobreposição com a plataforma
                if (j->vy > 0.0f) {
                    j->y = plataformas[i].y - j->altura;
                    j->vy = 0.0f;
                    j->no_chao = true;
                    j->pulos_restantes = j->pulo_duplo_liberado ? 2 : 1;
                }
                else if (j->vy < 0.0f) {
                    j->y = plataformas[i].y + plataformas[i].altura;
                    j->vy = 0.0f;
                }
            }
        }
    }
}

// Função para checar a coleta de itens pelo jogador
// Esta função verifica se o jogador colidiu com algum item no mundo e aplica os efeitos correspondentes.
int checar_coleta_itens(Jogador *j, ItemMundo itens[], int qtd_itens) {
    for (int i = 0; i < qtd_itens; i++) {
        if (!itens[i].ativo) continue;

        // Verifica se o jogador colidiu com o item usando a colisão AABB
        if (j->x + j->largura > itens[i].x && j->x < itens[i].x + itens[i].largura &&
            j->y + j->altura > itens[i].y && j->y < itens[i].y + itens[i].altura) {
            
            // Aplica os efeitos do item coletado pelo jogador
            if (itens[i].tipo == 1 || itens[i].tipo == 0) {
                j->pulo_duplo_liberado = true;
                j->pulos_restantes = 2; 
                itens[i].ativo = false; 
            }
            else if (itens[i].tipo == 2) {
                return 1;
            }
        }
    }
    return 0;
}

// Função para checar colisão AABB entre dois retângulos
bool checar_colisao_aabb(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2) {
    return (x1 + w1 > x2 && x1 < x2 + w2 &&
            y1 + h1 > y2 && y1 < y2 + h2);
}

// Função para processar o dano ao jogador
// Esta função verifica se o jogador colidiu com inimigos ou itens que causam dano
// e aplica o dano correspondente, além de ativar o timer de invulnerabilidade.
void processar_dano_jogador(Jogador *j, Inimigo inimigos[], int qtd_inimigos, ItemMundo itens[], int qtd_itens) {
    if (j->invulneravel_timer > 0) {
        j->invulneravel_timer--;
        return; 
    }

    bool tomou_dano = false;

    // Verifica colisão com inimigos
    for (int i = 0; i < qtd_inimigos; i++) {
        if (!inimigos[i].ativo) continue;
        if (checar_colisao_aabb(j->x, j->y, j->largura, j->altura, inimigos[i].x, inimigos[i].y, inimigos[i].largura, inimigos[i].altura)) {
            tomou_dano = true;
            break;
        }
    }

    // Verifica colisão com itens que causam dano (tipo 99)
    if (!tomou_dano) {
        for (int i = 0; i < qtd_itens; i++) {
            if (!itens[i].ativo || itens[i].tipo != 99) continue;
            if (checar_colisao_aabb(j->x, j->y, j->largura, j->altura, itens[i].x, itens[i].y, itens[i].largura, itens[i].altura)) {
                tomou_dano = true;
                break;
            }
        }
    }

    // Se o jogador tomou dano, reduz a vida, ativa o timer de invulnerabilidade e aplica um impulso para cima.
    if (tomou_dano) {
        j->vida--;
        j->invulneravel_timer = 60; 
        j->vy = -6.0f; 
        j->no_chao = false;
        j->escalando = false;
    }
}