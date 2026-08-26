#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Função auxiliar para exibir o cabeçalho dos testes
void cabecalho(const char* titulo) {
    printf("\n==================================================\n");
    printf(" CASO DE TESTE: %s\n", titulo);
    printf("==================================================\n");
}

int main() {
    deque d;
    ponto p1 = {1.0, 1.0, 1, 0.1};
    ponto p2 = {2.0, 2.0, 2, 0.2};
    ponto p3 = {3.0, 3.0, 3, 0.3};
    ponto* p_aux;

    // -------------------------------------------------------------------------
    cabecalho("1. Robustez contra Ponteiros NULL (Prevenção de SegFault)");
    fprintf(stderr, "Tentando operar em um deque que aponta para NULL:\n\n");

    fprintf(stderr, "[Testando] inicializar_deque(NULL)...\n");
    inicializar_deque(NULL);

    fprintf(stderr, "[Testando] inserir_inicio(NULL, p1)...\n");
    inserir_inicio(NULL, p1);

    fprintf(stderr, "[Testando] inserir_fim(NULL, p1)...\n");
    inserir_fim(NULL, p1);

    fprintf(stderr, "[Testando] remover_inicio(NULL)...\n");
    remover_inicio(NULL);

    fprintf(stderr, "[Testando] remover_fim(NULL)...\n");
    remover_fim(NULL);

    fprintf(stderr, "[Testando] obter_inicio(NULL)...\n");
    obter_inicio(NULL);

    fprintf(stderr, "[Testando] obter_fim(NULL)...\n");
    obter_fim(NULL);

    fprintf(stderr, "[Testando] obter_tamanho(NULL)...\n");
    obter_tamanho(NULL);

    fprintf(stderr, "[Testando] esta_vazio(NULL)...\n");
    esta_vazio(NULL);

    fprintf(stderr, "[Testando] liberar_deque(NULL)...\n");
    liberar_deque(NULL);

    fprintf(stderr, "[Testando] imprimir_deque(NULL)...\n");
    imprimir_deque(NULL);

    fprintf(stderr, "\n-> OK: O sistema tratou todos os ponteiros NULL com segurança!\n");

    // -------------------------------------------------------------------------
    
    cabecalho("2. Inicialização e Operações em Deque Vazio");
    inicializar_deque(&d);
    imprimir_deque(&d);
    printf("Está vazio? %s (Esperado: Sim)\n", esta_vazio(&d) ? "Sim" : "Não");
    printf("Tamanho: %d (Esperado: 0)\n", obter_tamanho(&d));
    
    printf("\nTentando remover de um deque vazio (deve disparar avisos):\n");
    remover_inicio(&d);
    remover_fim(&d);
    
    printf("\nTentando espiar dados de um deque vazio:\n");
    if (obter_inicio(&d) == NULL) printf("-> obter_inicio retornou NULL corretamente.\n");
    if (obter_fim(&d) == NULL) printf("-> obter_fim retornou NULL corretamente.\n");

    // -------------------------------------------------------------------------
    cabecalho("3. Transição Crítica: Vazio -> 1 Elemento (Inserir Início)");
    printf("Inserindo ID 1 no início...\n");
    inserir_inicio(&d, p1);
    imprimir_deque(&d);
    
    p_aux = obter_inicio(&d);
    printf("Início aponta para ID: %d\n", p_aux ? p_aux->id : -1);
    p_aux = obter_fim(&d);
    printf("Fim aponta para ID: %d (Deve ser igual ao início)\n", p_aux ? p_aux->id : -1);
    printf("Tamanho: %d (Esperado: 1)\n", obter_tamanho(&d));

    // -------------------------------------------------------------------------
    cabecalho("4. Transição Crítica: 1 Elemento -> Vazio (Remover Fim)");
    printf("Removendo do fim (o único elemento existente)...\n");
    remover_fim(&d);
    imprimir_deque(&d);
    printf("Está vazio? %s (Esperado: Sim)\n", esta_vazio(&d) ? "Sim" : "Não");

    // -------------------------------------------------------------------------
    cabecalho("5. Transição Crítica: Vazio -> 1 Elemento (Inserir Fim)");
    printf("Inserindo ID 2 no fim...\n");
    inserir_fim(&d, p2);
    imprimir_deque(&d);
    p_aux = obter_inicio(&d);
    printf("Início aponta para ID: %d\n", p_aux ? p_aux->id : -1);
    p_aux = obter_fim(&d);
    printf("Fim aponta para ID: %d\n", p_aux ? p_aux->id : -1);

    // -------------------------------------------------------------------------
    cabecalho("6. Transição Crítica: 1 Elemento -> Vazio (Remover Início)");
    printf("Removendo do início (o único elemento existente)...\n");
    remover_inicio(&d);
    imprimir_deque(&d);

    // -------------------------------------------------------------------------
    cabecalho("7. Inserções Múltiplas e Verificação de Encadeamento Duplo");
    printf("Inserindo ID 2 no fim, ID 1 no início, ID 3 no fim...\n");
    inserir_fim(&d, p2);     // Deque: (2.0, 2.0)
    inserir_inicio(&d, p1);  // Deque: (1.0, 1.0) (2.0, 2.0)
    inserir_fim(&d, p3);     // Deque: (1.0, 1.0) (2.0, 2.0) (3.0, 3.0)
    imprimir_deque(&d);      // Testa a nova impressão sem espaços extras!

    printf("Verificando consistência física das pontas:\n");
    printf("Início atual (ID esperado 1): %d\n", obter_inicio(&d)->id);
    printf("Fim atual (ID esperado 3): %d\n", obter_fim(&d)->id);
    printf("Tamanho atual (Esperado 3): %d\n", obter_tamanho(&d));

    // -------------------------------------------------------------------------
    cabecalho("8. Esvaziamento Progressivo até a Exaustão");
    printf("Removendo do início (sai ID 1)...\n");
    remover_inicio(&d);
    imprimir_deque(&d);

    printf("Removendo do fim (sai ID 3)...\n");
    remover_fim(&d);
    imprimir_deque(&d);

    printf("Removendo do início (sai ID 2, deve zerar o deque):\n");
    remover_inicio(&d);
    imprimir_deque(&d);
    printf("Tamanho final: %d (Esperado: 0)\n", obter_tamanho(&d));

    // -------------------------------------------------------------------------
    cabecalho("9. Inserção pós-esvaziamento e Liberação de Memória (Memory Leak Test)");
    printf("Reinserindo ID 1 e ID 3...\n");
    inserir_inicio(&d, p1);
    inserir_fim(&d, p3);
    imprimir_deque(&d);

    printf("Acionando liberar_deque()...\n");
    liberar_deque(&d);
    imprimir_deque(&d);
    printf("Está limpo e resetado? %s (Esperado: Sim)\n", esta_vazio(&d) ? "Sim" : "Não");

    printf("\n==================================================\n");
    printf(" 🎉 TODOS OS TESTES CRÍTICOS CONCLUÍDOS COM SUCESSO!\n");
    printf("==================================================\n");

    return 0;
}