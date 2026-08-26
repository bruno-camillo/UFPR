#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#define MAX_PLATAFORMAS 100
#define MAX_INIMIGOS     50
#define MAX_ITENS        50

// Enumeração para os estados de tela do jogo
typedef enum { 
    TELA_MENU, 
    TELA_JOGO, 
    TELA_PAUSA, 
    TELA_GAME_OVER,
    TELA_VITORIA
} estado_tela;

// Enumeração para os tipos de plataformas
typedef enum { 
    PLAT_FIXA = 0, 
    PLAT_MOVEL_VERT = 1, 
    PLAT_MOVEL_HORIZ = 2 
} tipo_plataforma;

// Enumeração para os tipos de inimigos
typedef enum { 
    INIMIGO_NORMAL = 0, 
    INIMIGO_VOADOR = 1, 
    INIMIGO_BOSS = 3 
} tipo_inimigo;

// Estrutura para o Jogador
typedef struct {
    float x, y;
    float vx, vy;
    int largura, altura;
    int vida;                  
    bool no_chao;
    int invulneravel_timer;    
    bool escalando;            
    bool pulo_duplo_liberado;  
    int pulos_restantes;       
    bool pode_cuspir;          
    bool agachado;             
    float stamina;             
    bool executando_dash;      
    int tempo_dash_restante;   
    int cooldown_dash;         
    float direcao_dash_x;      
    int frame_counter;
} Jogador;

// Estrutura para Plataformas no Mundo
typedef struct {
    float x, y;
    float largura, altura;
    int comportamento;         
    bool ativa;
    float direcao;             
    float limite_min;          
    float limite_max;          
} Plataforma;

// Estrutura para Inimigos no Mundo
typedef struct {
    float x, y;
    float vx, vy;
    int largura, altura;
    int tipo;                  
    int vida;
    bool ativo;
} Inimigo;

// Estrutura para Itens no Mundo
typedef struct {
    float x, y;
    float largura, altura;
    int tipo;                  
    bool ativo;
} ItemMundo;

// Gerenciador de Sprites
typedef struct {
    ALLEGRO_BITMAP *bg_camada1;    
    ALLEGRO_BITMAP *bg_camada2;    
    ALLEGRO_BITMAP *bg_camada3;    
    ALLEGRO_BITMAP *jogador_sheet;
    ALLEGRO_BITMAP *inimigo_roxo;
    ALLEGRO_BITMAP *inimigo_laranja;
    ALLEGRO_BITMAP *espinho;
    ALLEGRO_BITMAP *porta;          
    ALLEGRO_BITMAP *textura_pedra; 
    ALLEGRO_FONT   *fonte;         
    ALLEGRO_FONT   *fonte_titulo;    
    ALLEGRO_BITMAP *bg_menu;        
    ALLEGRO_BITMAP *btn_normal;      
    ALLEGRO_BITMAP *btn_focado;       
} GerenciadorSprites;

#endif