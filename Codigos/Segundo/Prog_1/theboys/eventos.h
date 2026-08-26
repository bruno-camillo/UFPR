#ifndef EVENTOS
#define EVENTOS

#include <stdbool.h>
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"

// struct que representa um heroi
struct heroi
{
	int id; // identificador do heroi
	struct cjto_t *hab; // habilidade especial do heroi
	int paci; // paciência do heroi
	int vel; // velocidade do heroi
	int xp; // experiência do heroi
	int base; // base que o heroi esta
    int status; // status do heroi (vivo ou morto)
}; 

// struct que representa uma coordenada no plano cartesiano (x,y)
struct coord
{
	int x; 
	int y;
};	

// struct que representa uma base
struct base
{
	int id; // identificador da base
	int lot; // lotação máxima da base
	struct cjto_t *pres; // conjunto de herois presentes na base 
	struct fila_t *esp; // fila de espera na base
	struct coord local; // coordenadas da base
	struct cjto_t *hab; // conjunto de habilidades que os herois da base possuem
	int missaoCompV;	// id da missao que executou um heroi com o uso do Composto V
	int participaMissao; // numero de participacoes em missoes
};

// struct que representa uma missão
struct missao
{
	int id; // identificador da missão
	struct cjto_t *hab; // conjunto de habilidades necessárias
	struct coord local; // coordenadas da missão
	int cumprida; // indica se a missao ja foi cumprida ou nao
	int tentativa; // numero de tentativas de cumprir a missao
};

struct mundo
{
	int nHerois; // número de herois no mundo
	struct heroi *herois; // vetor de herois
	int nBases; // número de bases no mundo
	struct base *bases; // vetor de bases
	int nMissoes; // número de missões no mundo
	struct missao *missoes; // vetor de missões
	int nHab; // número de habilidades no mundo
	int nCompostosV; // número de compostos de compostos V disponiveis
	struct coord tamMundo; // tamanho do mundo (coordenadas máximas)
	int relogio; // tempo atual do mundo
	int missoesCumpridas; // total de missoes cumpridas
	int tentativaMin; // menor numero de tentativas de uma missao
	int tentativaMax; // maior numero de tentativas de uma missao
	int somaTentativas; // quantidade total de tentativas
	float mediaTentativa; // media das tentativas
	int heroisMortos; // quantidade de herois mortos
	int nEventos; // numero de eventos
};

struct evento {
    void (*func)(struct mundo *, int, int, int, struct fprio_t*); // funcao com os determinados parametros, que definem eventos
    struct mundo *m; // mundo
    int T;  // instante do evento
    int idHeroi; // id do heroi presente no evento
    int idBase; // id da base presente no evento
    struct fprio_t *lef; // lista de eventos futuros
};  

struct evento_missao {
	void (*func)(struct mundo *, int, int, struct fprio_t*); // funcao com os determinados parametros, que definem missoes
	struct mundo *m;
	int T;
	int idMissao; // id da missao
	struct fprio_t *lef;
};

// Função para criar um novo evento
// Missao nao é incluida, pois eventos atuais nao envolvem missao diretamente
// Retorna 1 em caso de sucesso, e 0 caso contrario
int criaEvento(struct evento **e, void (*func)(struct mundo *, int, int, int, struct fprio_t*), struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// Funcao cria uma nova missao
// Retorna 1 em caso de sucesso e 0 caso contrario
int criaMissao (struct evento_missao **missao, void (*func)(struct mundo *, int, int, struct fprio_t*), struct mundo *m, int T, int idMissao, struct fprio_t *lef);

// Representa um heroi H chegando em uma base B no instante T. Ao chegar, o
// heroi analisa o tamanho da fila e decide se espera para entrar ou desiste
void CHEGA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// O heroi H entra na fila de espera da base B. Assim que H entrar na fila, o
// porteiro da base B deve ser avisado para verificar a fila
void ESPERA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// O heroi H desiste de entrar na base B, escolhe uma base aleatoria D e viaja
// para la
void DESISTE (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// O porteiro da base B trata a fila de espera
void AVISA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// O heroi H entra na base B. Ao entrar, o heroi decide quanto tempo vai ficar e
// agenda sua saıda da base
void ENTRA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// O heroi H sai da base B. Ao sair, escolhe uma base de destino para viajar; o
// porteiro de B e avisado, pois uma vaga foi liberada
void SAI (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// O heroi H se desloca para uma base D (que pode ser a mesma onde ja esta)
void VIAJA (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// O heroi H morre no instante T
void MORRE (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// Missao disparada no instante T
// Incrementa XP aos herois vivos caso seja concluida
// Eh realizada na base mais proxima com as habilidades necessarias
// Caso nenhuma base que cumpra os requisitos seja encontrada, a mais proxima de todas pode usar o Composto V
// O heroi mais experiente usa e morre em sequencia
void MISSAO (struct mundo *m, int T, int idMissao, struct fprio_t *lef);

// Encerra a simulacao no instante T
void FIM (struct mundo *m, int T, int idHeroi, int idBase, struct fprio_t *lef);

// inicializacao do mundo virtual
void INICIALIZA_MUNDO (struct mundo *m);

// destroi o mundo virtual, fazendo todas as liberacoes de memoria
void DESTROI_MUNDO (struct mundo *m);

// define as chegada de cada heroi numa determinada base
// alem de definir o tempo de cada missao
// insere ambos na lef
void EVENTOS_INICIAIS (struct mundo *m, struct fprio_t *lef);

#endif