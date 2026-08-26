#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "telas.h"

// Função para desenhar a tela de menu
// Esta função desenha o fundo, o título e os botões do menu principal, 
// destacando o botão selecionado.
void desenha_menu(int botao_selecionado, GerenciadorSprites *sprites) {
    al_clear_to_color(al_map_rgb(0, 0, 0)); 

    // Desenha o fundo do menu, se disponível
    if (sprites->bg_menu) {
        al_draw_scaled_bitmap(
            sprites->bg_menu, 
            0, 0, al_get_bitmap_width(sprites->bg_menu), al_get_bitmap_height(sprites->bg_menu), 
            0, -5, 1280, 730, 
            0
        );
    }

    // Título usando a fonte padrão única restaurada
    if (sprites->fonte) {
        al_draw_text(sprites->fonte, al_map_rgb(0, 0, 0), 643, 153, ALLEGRO_ALIGN_CENTER, "TRABALHO PROG 2");
        al_draw_text(sprites->fonte, al_map_rgb(255, 215, 0), 640, 150, ALLEGRO_ALIGN_CENTER, "TRABALHO PROG 2");
    }

    float btn_w = 320.0f; 
    float btn_h = 70.0f;  
    float btn_x = 640.0f - (btn_w / 2.0f); 

    int bbx, bby, text_w, text_h;

    // Botao JOGAR
    ALLEGRO_BITMAP *img_jogar = (botao_selecionado == 0) ? sprites->btn_focado : sprites->btn_normal;
    float jogar_y = 340.0f;

    // Desenha o botão JOGAR, destacando se estiver selecionado
    if (img_jogar) {
        al_draw_scaled_bitmap(img_jogar, 0, 0, al_get_bitmap_width(img_jogar), al_get_bitmap_height(img_jogar), btn_x, jogar_y, btn_w, btn_h, 0);
    } else {
        al_draw_filled_rectangle(btn_x, jogar_y, btn_x + btn_w, jogar_y + btn_h, (botao_selecionado == 0) ? al_map_rgb(255, 255, 0) : al_map_rgb(45, 45, 50));
    }
    
    // Desenha o texto do botão JOGAR, centralizado verticalmente e com cor dependendo da seleção
    if (sprites->fonte) {
        al_get_text_dimensions(sprites->fonte, "JOGAR", &bbx, &bby, &text_w, &text_h);
        float jogar_texto_centro_y = jogar_y + (btn_h / 2.0f) - (text_h / 2.0f) - bby;
        ALLEGRO_COLOR cor_txt = (botao_selecionado == 0) ? al_map_rgb(255, 255, 255) : al_map_rgb(180, 180, 180);
        
        // Desenha uma sombra para o texto do botão JOGAR para melhor visibilidade
        al_draw_text(sprites->fonte, al_map_rgb(0, 0, 0), 642, jogar_texto_centro_y + 2, ALLEGRO_ALIGN_CENTER, "JOGAR");
        al_draw_text(sprites->fonte, cor_txt, 640, jogar_texto_centro_y, ALLEGRO_ALIGN_CENTER, "JOGAR");
    }

    // Botao SAIR
    ALLEGRO_BITMAP *img_sair = (botao_selecionado == 1) ? sprites->btn_focado : sprites->btn_normal;
    float sair_y = 460.0f;

    // Desenha o botão SAIR, destacando se estiver selecionado
    if (img_sair) {
        al_draw_scaled_bitmap(img_sair, 0, 0, al_get_bitmap_width(img_sair), al_get_bitmap_height(img_sair), btn_x, sair_y, btn_w, btn_h, 0);
    } else {
        al_draw_filled_rectangle(btn_x, sair_y, btn_x + btn_w, sair_y + btn_h, (botao_selecionado == 1) ? al_map_rgb(255, 255, 0) : al_map_rgb(45, 45, 50));
    }
    
    // Desenha o texto do botão SAIR, centralizado verticalmente e com cor dependendo da seleção
    if (sprites->fonte) {
        al_get_text_dimensions(sprites->fonte, "SAIR", &bbx, &bby, &text_w, &text_h);
        float sair_texto_centro_y = sair_y + (btn_h / 2.0f) - (text_h / 2.0f) - bby;
        ALLEGRO_COLOR cor_txt = (botao_selecionado == 1) ? al_map_rgb(255, 255, 255) : al_map_rgb(180, 180, 180);
        
        al_draw_text(sprites->fonte, al_map_rgb(0, 0, 0), 642, sair_texto_centro_y + 2, ALLEGRO_ALIGN_CENTER, "SAIR");
        al_draw_text(sprites->fonte, cor_txt, 640, sair_texto_centro_y, ALLEGRO_ALIGN_CENTER, "SAIR");
    }
}

// Função para desenhar a tela de vitória
// Esta função desenha o fundo, o título e os botões da tela de vitória,
// destacando o botão selecionado.
void desenha_pausa(int botao_selecionado, GerenciadorSprites *sprites) {
    al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(0, 0, 0, 150));
    al_draw_filled_rectangle(380, 100, 900, 580, al_map_rgba(25, 25, 35, 220));
    al_draw_rectangle(380, 100, 900, 580, al_map_rgb(0, 255, 255), 2);

    // Se a fonte estiver carregada, desenha o título "JOGO PAUSADO" no topo da tela de pausa
    if (sprites->fonte) al_draw_text(sprites->fonte, al_map_rgb(0, 255, 255), 640, 130, ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO");

    float btn_w = 280.0f, btn_h = 60.0f, btn_x = 640.0f - (btn_w / 2.0f);
    char *textos[] = {"RETOMAR", "MENU", "SAIR"};
    float pos_y[] = {230, 335, 440};

    int bbx, bby, text_w, text_h;

    // Desenha os botões da tela de pausa, destacando o botão selecionado e centralizando o texto verticalmente
    for (int i = 0; i < 3; i++) {
        ALLEGRO_BITMAP *img = (botao_selecionado == i) ? sprites->btn_focado : sprites->btn_normal;
        if (img) {
            al_draw_scaled_bitmap(img, 0, 0, al_get_bitmap_width(img), al_get_bitmap_height(img), btn_x, pos_y[i], btn_w, btn_h, 0);
        } else {
            al_draw_filled_rectangle(btn_x, pos_y[i], btn_x + btn_w, pos_y[i] + btn_h, (botao_selecionado == i) ? al_map_rgb(255, 255, 0) : al_map_rgb(45, 45, 55));
        }
        
        // Se a fonte estiver carregada, desenha o texto do botão, 
        // centralizando verticalmente e ajustando a cor dependendo da seleção  
        if (sprites->fonte) {
            al_get_text_dimensions(sprites->fonte, textos[i], &bbx, &bby, &text_w, &text_h);
            float centro_y_pausa = pos_y[i] + (btn_h / 2.0f) - (text_h / 2.0f) - bby;
            ALLEGRO_COLOR c = (botao_selecionado == i) ? al_map_rgb(255, 255, 255) : al_map_rgb(170, 170, 170);
            
            al_draw_text(sprites->fonte, al_map_rgb(0, 0, 0), 642, centro_y_pausa + 2, ALLEGRO_ALIGN_CENTER, textos[i]);
            al_draw_text(sprites->fonte, c, 640, centro_y_pausa, ALLEGRO_ALIGN_CENTER, textos[i]);
        }
    }
}

// Função para desenhar a tela de game over
// Esta função desenha o fundo, o título e os botões da tela de game over
// destacando o botão selecionado.
void desenha_game_over(int botao_selecionado, GerenciadorSprites *sprites) {
    al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(40, 5, 5, 160)); 
    al_draw_filled_rectangle(380, 100, 900, 580, al_map_rgba(30, 20, 20, 230));
    al_draw_rectangle(380, 100, 900, 580, al_map_rgb(220, 20, 60), 3);

    // Se a fonte estiver carregada, desenha o título "GAME OVER" no topo da tela de game over
    if (sprites->fonte) al_draw_text(sprites->fonte, al_map_rgb(255, 40, 40), 640, 130, ALLEGRO_ALIGN_CENTER, "GAME OVER");

    float btn_w = 300.0f, btn_h = 60.0f, btn_x = 640.0f - (btn_w / 2.0f);
    char *textos[] = {"RETOMAR", "MENU", "SAIR"};
    float pos_y[] = {230, 335, 440};

    int bbx, bby, text_w, text_h;

    // Desenha os botões da tela de game over, destacando o botão selecionado e centralizando o texto verticalmente
    for (int i = 0; i < 3; i++) {
        ALLEGRO_BITMAP *img = (botao_selecionado == i) ? sprites->btn_focado : sprites->btn_normal;
        // Se a imagem do botão estiver disponível, desenha o bitmap do botão, caso contrário, desenha um retângulo preenchido
        if (img) {
            al_draw_scaled_bitmap(img, 0, 0, al_get_bitmap_width(img), al_get_bitmap_height(img), btn_x, pos_y[i], btn_w, btn_h, 0);
        } else {
            al_draw_filled_rectangle(btn_x, pos_y[i], btn_x + btn_w, pos_y[i] + btn_h, (botao_selecionado == i) ? al_map_rgb(255, 255, 0) : al_map_rgb(50, 40, 40));
        }
        // Se a fonte estiver carregada, desenha o texto do botão,
        // centralizando verticalmente e ajustando a cor dependendo da seleção
        if (sprites->fonte) {
            al_get_text_dimensions(sprites->fonte, textos[i], &bbx, &bby, &text_w, &text_h);
            float centro_y_gameover = pos_y[i] + (btn_h / 2.0f) - (text_h / 2.0f) - bby;
            ALLEGRO_COLOR c = (botao_selecionado == i) ? al_map_rgb(255, 255, 255) : al_map_rgb(170, 170, 170);
            
            al_draw_text(sprites->fonte, al_map_rgb(0, 0, 0), 642, centro_y_gameover + 2, ALLEGRO_ALIGN_CENTER, textos[i]);
            al_draw_text(sprites->fonte, c, 640, centro_y_gameover, ALLEGRO_ALIGN_CENTER, textos[i]);
        }
    }
}

// Função para desenhar a tela de vitória
// Esta função desenha o fundo, o título e os botões da tela de vitória
// destacando o botão selecionado.
void desenha_jogo(Jogador *j, Inimigo inimigos[], int qtd_inimigos, Plataforma plataformas[], int qtd_plataformas, ItemMundo itens[], int qtd_itens, GerenciadorSprites *sprites, float camera_x) {
    // Se a imagem de fundo da camada 1 estiver disponível, desenha o fundo com efeito de paralaxe
    if (sprites->bg_camada1) {
        float bg1_x = -((int)(camera_x * 0.05f) % 1280);
        int img_w = al_get_bitmap_width(sprites->bg_camada1);
        int img_h = al_get_bitmap_height(sprites->bg_camada1);
        al_draw_scaled_bitmap(sprites->bg_camada1, 0, 0, img_w, img_h, bg1_x, 0, 1280, 720, 0);
        al_draw_scaled_bitmap(sprites->bg_camada1, 0, 0, img_w, img_h, bg1_x + 1280, 0, 1280, 720, 0);
    } else {
        al_clear_to_color(al_map_rgb(135, 206, 235)); 
    }
    // Se a imagem de fundo da camada 2 estiver disponível, desenha o fundo com efeito de paralaxe
    if (sprites->bg_camada2) {
        float bg2_x = -((int)(camera_x * 0.20f) % 1280);
        int img_w = al_get_bitmap_width(sprites->bg_camada2);
        int img_h = al_get_bitmap_height(sprites->bg_camada2);
        al_draw_scaled_bitmap(sprites->bg_camada2, 0, 0, img_w, img_h, bg2_x, 0, 1280, 720, 0);
        al_draw_scaled_bitmap(sprites->bg_camada2, 0, 0, img_w, img_h, bg2_x + 1280, 0, 1280, 720, 0);
    }
    // Se a imagem de fundo da camada 3 estiver disponível, desenha o fundo com efeito de paralaxe
    for (int i = 0; i < qtd_plataformas; i++) {
        if (!plataformas[i].ativa) continue;
        if (sprites->textura_pedra) {
            float tam_bloco = 40.0f; 
            for (float px = plataformas[i].x; px < plataformas[i].x + plataformas[i].largura; px += tam_bloco) {
                for (float py = plataformas[i].y; py < plataformas[i].y + plataformas[i].altura; py += tam_bloco) {
                    float larg_recorte = (px + tam_bloco > plataformas[i].x + plataformas[i].largura) ? (plataformas[i].x + plataformas[i].largura - px) : tam_bloco;
                    float alt_recorte = (py + tam_bloco > plataformas[i].y + plataformas[i].altura) ? (plataformas[i].y + plataformas[i].altura - py) : tam_bloco;
                    al_draw_scaled_bitmap(sprites->textura_pedra, 0, 0, al_get_bitmap_width(sprites->textura_pedra), al_get_bitmap_height(sprites->textura_pedra), px - camera_x, py, larg_recorte, alt_recorte, 0);
                }
            }
        } else {
            ALLEGRO_COLOR cor = al_map_rgb(255, 0, 0); 
            if (plataformas[i].comportamento != 0) cor = al_map_rgb(120, 120, 120); 
            al_draw_filled_rectangle(plataformas[i].x - camera_x, plataformas[i].y, plataformas[i].x + plataformas[i].largura - camera_x, plataformas[i].y + plataformas[i].altura, cor);
        }
    }
    // Desenha os itens no mundo, verificando o tipo de cada item e desenhando a representação apropriada
    for (int i = 0; i < qtd_itens; i++) {
        if (!itens[i].ativo) continue;
        // Se o item for do tipo 99 (espinho), desenha o sprite do espinho ou um triângulo vermelho se o sprite não estiver disponível
        if (itens[i].tipo == 99) { 
            if (sprites->espinho) al_draw_scaled_bitmap(sprites->espinho, 0, 0, al_get_bitmap_width(sprites->espinho), al_get_bitmap_height(sprites->espinho), itens[i].x - camera_x, itens[i].y, itens[i].largura, itens[i].altura, 0);
            else al_draw_filled_triangle(itens[i].x - camera_x, itens[i].y + itens[i].altura, itens[i].x + (itens[i].largura / 2.0f) - camera_x, itens[i].y, itens[i].x + itens[i].largura - camera_x, itens[i].y + itens[i].altura, al_map_rgb(220, 20, 60));
        } 
        // Se o item for do tipo 0 ou 1 (pulo duplo), desenha uma elipse ciano representando o item
        else if (itens[i].tipo == 0 || itens[i].tipo == 1) { 
            al_draw_filled_ellipse(itens[i].x + (itens[i].largura / 2.0f) - camera_x, itens[i].y + (itens[i].altura / 2.0f), itens[i].largura / 2.0f, itens[i].altura / 2.0f, al_map_rgb(0, 255, 255)); 
        } 
        // Se o item for do tipo 2 (porta final), desenha o sprite da porta ou um retângulo marrom se o sprite não estiver disponível
        else if (itens[i].tipo == 2) { 
            // Se o sprite da porta estiver disponível, desenha o sprite da porta, caso contrário, desenha um retângulo marrom representando a porta
            if (sprites->porta) al_draw_scaled_bitmap(sprites->porta, 0, 0, al_get_bitmap_width(sprites->porta), al_get_bitmap_height(sprites->porta), itens[i].x - camera_x, itens[i].y, itens[i].largura, itens[i].altura, 0); 
            else al_draw_filled_rectangle(itens[i].x - camera_x, itens[i].y, itens[i].x + itens[i].largura - camera_x, itens[i].y + itens[i].altura, al_map_rgb(139, 69, 19));
        }
    }

    // Desenha os inimigos no mundo, verificando o tipo de cada inimigo e desenhando a representação apropriada
    for (int i = 0; i < qtd_inimigos; i++) {
        if (!inimigos[i].ativo) continue;
        ALLEGRO_BITMAP *img_inimigo = (inimigos[i].tipo == 0) ? sprites->inimigo_roxo : sprites->inimigo_laranja;
        int flags = (inimigos[i].vx < 0.0f) ? ALLEGRO_FLIP_HORIZONTAL : 0;
        float escala_largura = 2.2f; 
        float escala_altura  = 1.3f; 

        // Se o sprite do inimigo estiver disponível, desenha o sprite do inimigo, caso contrário, desenha um retângulo representando o inimigo
        if (img_inimigo) {
            al_draw_scaled_bitmap(img_inimigo, 0, 0, al_get_bitmap_width(img_inimigo), al_get_bitmap_height(img_inimigo), inimigos[i].x - camera_x, inimigos[i].y - (inimigos[i].altura * (escala_altura - 1.0f)), inimigos[i].largura * escala_largura, inimigos[i].altura * escala_altura, flags);
        } else {
            ALLEGRO_COLOR c = (inimigos[i].tipo == 0) ? al_map_rgb(148, 0, 211) : al_map_rgb(255, 140, 0);
            al_draw_filled_rectangle(inimigos[i].x - camera_x, inimigos[i].y, inimigos[i].x + inimigos[i].largura - camera_x, inimigos[i].y + inimigos[i].altura, c);
        }
    }

    // Desenha o jogador, verificando o estado do jogador e desenhando a representação apropriada
    if (j->invulneravel_timer == 0 || (j->invulneravel_timer % 4 < 2)) {
        if (sprites->jogador_sheet) {
            int src_x = 0;
            if (j->executando_dash) src_x = 6 * 50; 
            else if (j->escalando) src_x = 3 * 50; 
            else if (!j->no_chao) src_x = 1 * 50; 
            else if (j->agachado) src_x = 2 * 50; 
            else if (j->vx != 0.0f) src_x = (4 + ((j->frame_counter / 10) % 2)) * 50; 
            else src_x = 0 * 50;

            int flags = (j->direcao_dash_x < 0.0f) ? ALLEGRO_FLIP_HORIZONTAL : 0;
            al_draw_scaled_bitmap(sprites->jogador_sheet, src_x, 0, 50, 100, j->x - camera_x, j->y, j->largura, j->altura, flags);
        } else {
            ALLEGRO_COLOR c = j->executando_dash ? al_map_rgb(255, 215, 0) : (j->escalando ? al_map_rgb(0, 255, 200) : al_map_rgb(0, 0, 255));
            al_draw_filled_rectangle(j->x - camera_x, j->y, j->x + j->largura - camera_x, j->y + j->altura, c);
        }
    }

    // Desenha a HUD do jogador, incluindo a vida e a barra de stamina
    for (int v = 0; v < 3; v++) {
        float pos_hud_x = 40.0f + (v * 40.0f), pos_hud_y = 30.0f;
        ALLEGRO_COLOR c_cor = (v < j->vida) ? al_map_rgb(255, 0, 0) : al_map_rgb(60, 60, 60);
        al_draw_filled_circle(pos_hud_x - 7, pos_hud_y, 8, c_cor); al_draw_filled_circle(pos_hud_x + 7, pos_hud_y, 8, c_cor);
        al_draw_filled_triangle(pos_hud_x - 15, pos_hud_y + 2, pos_hud_x + 15, pos_hud_y + 2, pos_hud_x, pos_hud_y + 16, c_cor);
    }
    al_draw_filled_rectangle(25, 55, 145, 65, al_map_rgb(50, 50, 50));

    // Desenha a barra de stamina do jogador, preenchendo proporcionalmente à quantidade de stamina restante
    if (j->stamina > 0.0f) al_draw_filled_rectangle(25, 55, 25 + ((j->stamina / 100.0f) * 120.0f), 65, al_map_rgb(255, 215, 0));
    al_draw_rectangle(25, 55, 145, 65, al_map_rgb(0, 0, 0), 1);
}

// Função para desenhar a tela de vitória
// Esta função desenha o fundo, o título e os botões da tela de vitória
// destacando o botão selecionado.
void desenha_vitoria(int botao_selecionado, GerenciadorSprites *sprites) {
    // Névoa dourada/esverdeada semitransparente de vitória sobre o jogo de fundo
    al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(10, 40, 20, 150)); 

    al_draw_filled_rectangle(380, 120, 900, 560, al_map_rgba(20, 35, 25, 230));
    al_draw_rectangle(380, 120, 900, 560, al_map_rgb(255, 215, 0), 3); // Borda Dourada

    // Se a fonte estiver carregada, desenha o título "VOCÊ VENCEU!" no topo da tela de vitória com sombra para destaque
    if (sprites->fonte) {
        al_draw_text(sprites->fonte, al_map_rgb(0, 0, 0), 642, 152, ALLEGRO_ALIGN_CENTER, "VOCÊ VENCEU!");
        al_draw_text(sprites->fonte, al_map_rgb(255, 215, 0), 640, 150, ALLEGRO_ALIGN_CENTER, "VOCÊ VENCEU!");
    }

    float btn_w = 320.0f, btn_h = 70.0f, btn_x = 640.0f - (btn_w / 2.0f);
    char *textos[] = {"MENU INICIAL", "SAIR DO JOGO"};
    float pos_y[] = {270, 390}; // Duas opções de botões

    int bbx, bby, text_w, text_h;

    // Desenha os botões da tela de vitória, destacando o botão selecionado e centralizando o texto verticalmente
    for (int i = 0; i < 2; i++) {
        ALLEGRO_BITMAP *img = (botao_selecionado == i) ? sprites->btn_focado : sprites->btn_normal;
        // Se a imagem do botão estiver disponível, desenha o bitmap do botão, caso contrário, desenha um retângulo preenchido
        if (img) {
            al_draw_scaled_bitmap(img, 0, 0, al_get_bitmap_width(img), al_get_bitmap_height(img), btn_x, pos_y[i], btn_w, btn_h, 0);
        } else {
            al_draw_filled_rectangle(btn_x, pos_y[i], btn_x + btn_w, pos_y[i] + btn_h, (botao_selecionado == i) ? al_map_rgb(255, 255, 0) : al_map_rgb(45, 50, 45));
        }
        
        // Se a fonte estiver carregada, desenha o texto do botão,
        // centralizando verticalmente e ajustando a cor dependendo da seleção
        if (sprites->fonte) {
            // Centralização Y Matemática absoluta para tamanho 32
            al_get_text_dimensions(sprites->fonte, textos[i], &bbx, &bby, &text_w, &text_h);
            float centro_y_vitoria = pos_y[i] + (btn_h / 2.0f) - (text_h / 2.0f) - bby;
            ALLEGRO_COLOR c = (botao_selecionado == i) ? al_map_rgb(255, 255, 255) : al_map_rgb(170, 170, 170);
            
            al_draw_text(sprites->fonte, al_map_rgb(0, 0, 0), 642, centro_y_vitoria + 2, ALLEGRO_ALIGN_CENTER, textos[i]);
            al_draw_text(sprites->fonte, c, 640, centro_y_vitoria, ALLEGRO_ALIGN_CENTER, textos[i]);
        }
    }
}