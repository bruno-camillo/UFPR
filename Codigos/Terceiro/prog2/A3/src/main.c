#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_font.h>  
#include <allegro5/allegro_ttf.h>   
#include "estruturas.h"
#include "mapa.h"
#include "jogador.h"
#include "inimigo.h"
#include "telas.h"

#define JANELA_LARGURA 1280
#define JANELA_ALTURA  720

int main() {
    // Inicialização dos Subsistemas do Allegro 5
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_image_addon(); 
    al_init_font_addon();           
    al_init_ttf_addon();            

    ALLEGRO_DISPLAY *display = al_create_display(JANELA_LARGURA, JANELA_ALTURA);
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    // Variáveis de Estado de Jogo e Interface
    estado_tela tela_atual = TELA_MENU; 
    int botao_menu_selecionado = 0;
    int botao_pausa_selecionado = 0;
    int botao_game_over_selecionado = 0;
    int botao_vitoria_selecionado = 0; 

    // Entidades Lógicas
    Jogador player;
    Plataforma plataformas[MAX_PLATAFORMAS];
    Inimigo inimigos[MAX_INIMIGOS];
    ItemMundo itens[MAX_ITENS];

    int qtd_plat = 0, qtd_inim = 0, qtd_itens = 0;
    float camera_x = 0.0f;

    // Carregamento do Gerenciador de Sprites
    GerenciadorSprites sprites;
    sprites.bg_camada1      = al_load_bitmap("sprites/bg_camada1.png");
    sprites.bg_camada2      = al_load_bitmap("sprites/bg_camada2.png");
    sprites.jogador_sheet   = al_load_bitmap("sprites/jogador_sprites.png");
    sprites.inimigo_roxo    = al_load_bitmap("sprites/inimigo_roxo.png");
    sprites.inimigo_laranja = al_load_bitmap("sprites/inimigo_laranja.png");
    sprites.espinho         = al_load_bitmap("sprites/espinhos.png");
    sprites.porta           = al_load_bitmap("sprites/porta.png");
    sprites.textura_pedra   = al_load_bitmap("sprites/pedra.png"); 
    
    // Texturas para a interface visual do menu
    sprites.bg_menu         = al_load_bitmap("sprites/bg_menu.png");
    sprites.btn_normal      = al_load_bitmap("sprites/btn_normal.png");
    sprites.btn_focado      = al_load_bitmap("sprites/btn_focado.png");

    // Carregamento de Fonte Unificado tamanho 32 para os botões
    sprites.fonte = al_load_ttf_font("sprites/arial.ttf", 32, 0);
    if (!sprites.fonte) {
        sprites.fonte = al_load_ttf_font("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 32, 0);
    }
    if (!sprites.fonte) {
        sprites.fonte = al_load_ttf_font("C:\\Windows\\Fonts\\arial.ttf", 32, 0);
    }
    if (!sprites.fonte) {
        sprites.fonte = al_create_builtin_font();
    }

    // Inicialização Inicial lendo os ficheiros de texto
    inicializar_jogador(&player);
    carregar_dados_mundo(plataformas, &qtd_plat, inimigos, &qtd_inim, itens, &qtd_itens);

    al_start_timer(timer);
    bool rodando = true;
    bool teclas[ALLEGRO_KEY_MAX] = {false};

    // Loop Principal de Eventos 
    while (rodando) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(queue, &evento);

        // Processamento de Eventos
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            rodando = false;
        }

        else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            teclas[evento.keyboard.keycode] = true;
            // Navegação entre telas e ações do jogador
            if (tela_atual == TELA_MENU) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) botao_menu_selecionado = (botao_menu_selecionado + 1) % 2; 
                if (evento.keyboard.keycode == ALLEGRO_KEY_UP)   botao_menu_selecionado = (botao_menu_selecionado - 1 + 2) % 2;
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    if (botao_menu_selecionado == 0) {
                        inicializar_jogador(&player);
                        carregar_dados_mundo(plataformas, &qtd_plat, inimigos, &qtd_inim, itens, &qtd_itens);
                        camera_x = 0.0f;
                        tela_atual = TELA_JOGO;
                    }
                    else rodando = false;
                }
            }
            
            else if (tela_atual == TELA_JOGO) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_UP) {
                    if (player.escalando) {
                        player.vy = -10.0f; player.vx = (player.direcao_dash_x > 0.0f) ? -5.0f : 5.0f;
                        player.x += player.vx; player.escalando = false;
                    }
                    else if (!player.agachado) {
                        if (player.no_chao) { player.vy = -12.0f; player.pulos_restantes--; }
                        else if (player.pulos_restantes > 0 && player.pulo_duplo_liberado) { player.vy = -11.0f; player.pulos_restantes--; }
                    }
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_LSHIFT && !player.executando_dash && !player.agachado && !player.escalando) {
                    if (player.stamina >= 40.0f && player.cooldown_dash == 0) {
                        player.executando_dash = true; player.tempo_dash_restante = 12; player.cooldown_dash = 45; player.stamina -= 40.0f;
                    }
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { botao_pausa_selecionado = 0; tela_atual = TELA_PAUSA; }
            }

            else if (tela_atual == TELA_PAUSA) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) botao_pausa_selecionado = (botao_pausa_selecionado + 1) % 3; 
                if (evento.keyboard.keycode == ALLEGRO_KEY_UP)   botao_pausa_selecionado = (botao_pausa_selecionado - 1 + 3) % 3;
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    if (botao_pausa_selecionado == 0) tela_atual = TELA_JOGO; 
                    else if (botao_pausa_selecionado == 1) { inicializar_jogador(&player); carregar_dados_mundo(plataformas, &qtd_plat, inimigos, &qtd_inim, itens, &qtd_itens); camera_x = 0.0f; tela_atual = TELA_MENU; }
                    else if (botao_pausa_selecionado == 2) rodando = false; 
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) tela_atual = TELA_JOGO;
            }

            else if (tela_atual == TELA_GAME_OVER) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) botao_game_over_selecionado = (botao_game_over_selecionado + 1) % 3;
                if (evento.keyboard.keycode == ALLEGRO_KEY_UP)   botao_game_over_selecionado = (botao_game_over_selecionado - 1 + 3) % 3;
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    if (botao_game_over_selecionado == 0) { inicializar_jogador(&player); carregar_dados_mundo(plataformas, &qtd_plat, inimigos, &qtd_inim, itens, &qtd_itens); camera_x = 0.0f; tela_atual = TELA_JOGO; }
                    else if (botao_game_over_selecionado == 1) { inicializar_jogador(&player); carregar_dados_mundo(plataformas, &qtd_plat, inimigos, &qtd_inim, itens, &qtd_itens); camera_x = 0.0f; tela_atual = TELA_MENU; }
                    else if (botao_game_over_selecionado == 2) rodando = false; 
                }
            }

            else if (tela_atual == TELA_VITORIA) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) botao_vitoria_selecionado = (botao_vitoria_selecionado + 1) % 2;
                if (evento.keyboard.keycode == ALLEGRO_KEY_UP)   botao_vitoria_selecionado = (botao_vitoria_selecionado - 1 + 2) % 2;
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    if (botao_vitoria_selecionado == 0) { 
                        inicializar_jogador(&player); 
                        carregar_dados_mundo(plataformas, &qtd_plat, inimigos, &qtd_inim, itens, &qtd_itens); 
                        camera_x = 0.0f; 
                        tela_atual = TELA_MENU; 
                    }
                    else if (botao_vitoria_selecionado == 1) rodando = false; 
                }
            }
        }
        // Processamento de Eventos de Teclado
        else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
            teclas[evento.keyboard.keycode] = false;
        }
        // Processamento de Eventos de Timer (Atualização do Jogo e Renderização)
        else if (evento.type == ALLEGRO_EVENT_TIMER) {
            if (tela_atual == TELA_JOGO) {
                player.frame_counter++; 
                if (!player.executando_dash && !player.escalando) {
                    player.vx = 0;
                    if (teclas[ALLEGRO_KEY_LEFT])  player.vx = -4.0f; 
                    if (teclas[ALLEGRO_KEY_RIGHT]) player.vx = 4.0f;  
                }
                if (player.escalando) {
                    player.vy = 0.8f; 
                    if (teclas[ALLEGRO_KEY_UP])    player.vy = -3.0f; 
                    if (teclas[ALLEGRO_KEY_DOWN])  player.vy = 3.0f;  
                }
                // Atualizações de Entidades e Lógica do Jogo
                atualizar_plataformas_moveis(plataformas, qtd_plat);
                atualizar_jogador(&player, plataformas, qtd_plat, teclas[ALLEGRO_KEY_DOWN]);
                atualizar_inimigos(inimigos, qtd_inim, plataformas, qtd_plat);
                processar_dano_jogador(&player, inimigos, qtd_inim, itens, qtd_itens);

                if (player.vida <= 0 || player.y > JANELA_ALTURA) { botao_game_over_selecionado = 0; tela_atual = TELA_GAME_OVER; }
                
                // Quando chega na porta, checar_coleta_itens retorna 1, joga para a TELA_VITORIA em vez de Game Over
                if (checar_coleta_itens(&player, itens, qtd_itens) == 1) { botao_vitoria_selecionado = 0; tela_atual = TELA_VITORIA; }

                camera_x = player.x - (JANELA_LARGURA / 2.0f);
                if (camera_x < 0.0f)   camera_x = 0.0f;
                if (camera_x > 6170.0f) camera_x = 6170.0f;
            }

            // Árvore de Telas 
            if (tela_atual == TELA_MENU) {
                desenha_menu(botao_menu_selecionado, &sprites);
            } 
            else if (tela_atual == TELA_JOGO) {
                desenha_jogo(&player, inimigos, qtd_inim, plataformas, qtd_plat, itens, qtd_itens, &sprites, camera_x);
            } 
            else if (tela_atual == TELA_PAUSA) {
                desenha_jogo(&player, inimigos, qtd_inim, plataformas, qtd_plat, itens, qtd_itens, &sprites, camera_x);
                desenha_pausa(botao_pausa_selecionado, &sprites);
            } 
            else if (tela_atual == TELA_GAME_OVER) {
                desenha_jogo(&player, inimigos, qtd_inim, plataformas, qtd_plat, itens, qtd_itens, &sprites, camera_x);
                desenha_game_over(botao_game_over_selecionado, &sprites);
            }
            else if (tela_atual == TELA_VITORIA) {
                desenha_jogo(&player, inimigos, qtd_inim, plataformas, qtd_plat, itens, qtd_itens, &sprites, camera_x);
                desenha_vitoria(botao_vitoria_selecionado, &sprites);
            }

            al_flip_display();
        }
    }

    // Liberação Estruturada de Memória
    if (sprites.bg_camada1)      al_destroy_bitmap(sprites.bg_camada1);
    if (sprites.bg_camada2)      al_destroy_bitmap(sprites.bg_camada2);
    if (sprites.jogador_sheet)   al_destroy_bitmap(sprites.jogador_sheet);
    if (sprites.inimigo_roxo)    al_destroy_bitmap(sprites.inimigo_roxo);
    if (sprites.inimigo_laranja) al_destroy_bitmap(sprites.inimigo_laranja);
    if (sprites.espinho)         al_destroy_bitmap(sprites.espinho);
    if (sprites.porta)           al_destroy_bitmap(sprites.porta);
    if (sprites.textura_pedra)   al_destroy_bitmap(sprites.textura_pedra); 
    if (sprites.bg_menu)         al_destroy_bitmap(sprites.bg_menu);
    if (sprites.btn_normal)      al_destroy_bitmap(sprites.btn_normal);
    if (sprites.btn_focado)      al_destroy_bitmap(sprites.btn_focado);
    if (sprites.fonte)           al_destroy_font(sprites.fonte); 

    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_display(display);
    return 0;
}