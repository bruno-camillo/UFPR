#include "inimigo.h"

// Função para atualizar a posição e o comportamento dos inimigos
// Esta função aplica a gravidade, verifica colisões com plataformas 
// e implementa a lógica de patrulha dos inimigos.
void atualizar_inimigos(Inimigo inimigos[], int qtd_inimigos, Plataforma plataformas[], int qtd_plataformas) {
    for (int i = 0; i < qtd_inimigos; i++) {
        if (!inimigos[i].ativo) continue;

        inimigos[i].vy += 0.5f; 

        // Movimentação e colisão no eixo X (Patrulha)
        inimigos[i].x += inimigos[i].vx;
        bool bateu_na_parede = false;

        // Verificação de colisão com plataformas no eixo X
        for (int p = 0; p < qtd_plataformas; p++) {
            if (!plataformas[p].ativa) continue;

            // Verifica se o inimigo colidiu com a plataforma no eixo X
            if (inimigos[i].x + inimigos[i].largura > plataformas[p].x && inimigos[i].x < plataformas[p].x + plataformas[p].largura &&
                inimigos[i].y + inimigos[i].altura > plataformas[p].y && inimigos[i].y < plataformas[p].y + plataformas[p].altura) {
                
                // Ajusta a posição do inimigo para evitar sobreposição com a plataforma
                if (inimigos[i].vx > 0.0f) {
                    inimigos[i].x = plataformas[p].x - inimigos[i].largura;
                    bateu_na_parede = true;
                }
                else if (inimigos[i].vx < 0.0f) {
                    inimigos[i].x = plataformas[p].x + plataformas[p].largura;
                    bateu_na_parede = true;
                }
            }
        }

        // Movimentação e colisão no eixo Y (Gravidade)
        inimigos[i].y += inimigos[i].vy;
        bool no_chao = false;

        // Verificação de colisão com plataformas no eixo Y
        for (int p = 0; p < qtd_plataformas; p++) {
            if (!plataformas[p].ativa) continue;

            // Verifica se o inimigo colidiu com a plataforma no eixo Y
            if (inimigos[i].x + inimigos[i].largura > plataformas[p].x && inimigos[i].x < plataformas[p].x + plataformas[p].largura &&
                inimigos[i].y + inimigos[i].altura > plataformas[p].y && inimigos[i].y < plataformas[p].y + plataformas[p].altura) {
                
                // Ajusta a posição do inimigo para evitar sobreposição com a plataforma
                if (inimigos[i].vy > 0.0f) {
                    inimigos[i].y = plataformas[p].y - inimigos[i].altura;
                    inimigos[i].vy = 0.0f;
                    no_chao = true; 
                }
            }
        }

        // Lógica de patrulha: se o inimigo estiver no chão, verifica se há chão à frente; caso contrário, inverte a direção
        if (no_chao) {
            if (bateu_na_parede) {
                inimigos[i].vx = -inimigos[i].vx;
            } else {
                float proximo_x = (inimigos[i].vx > 0.0f) ? (inimigos[i].x + inimigos[i].largura) : inimigos[i].x;
                float chao_abaixo_y = inimigos[i].y + inimigos[i].altura + 5.0f; 
                
                bool chao_detectado = false;

                for (int p = 0; p < qtd_plataformas; p++) {
                    // Se a plataforma não estiver ativa, ignora a verificação
                    if (!plataformas[p].ativa) continue;
                    // Se o próximo ponto à frente do inimigo estiver sobre uma plataforma, considera que há chão
                    if (proximo_x >= plataformas[p].x && proximo_x <= plataformas[p].x + plataformas[p].largura &&
                        chao_abaixo_y >= plataformas[p].y && chao_abaixo_y <= plataformas[p].y + plataformas[p].altura) {
                        chao_detectado = true;
                        break;
                    }
                }

                if (!chao_detectado) {
                    inimigos[i].vx = -inimigos[i].vx;
                }
            }
        }
    }
}