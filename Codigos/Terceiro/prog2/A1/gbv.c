#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gbv.h"
#include "util.h"

// Variavel global estatica para armazenar o nome do arquivo container,
// ja que a assinatura de gbv_remover imposta pelo cabecalho nao recebe o nome_arquivo.
char arquivo_atual[MAX_NOME];

// Le o superbloco no inicio do arquivo para pegar o numero de documentos e o deslocamento do diretorio
// Retorna 0 se leu com sucesso ou -1 em caso de erro
int leSuperbloco (FILE *f, int *quantidade, long *deslocamento_dir) {
    if (!f || !quantidade || !deslocamento_dir)
        return -1;

    fseek(f, 0, SEEK_SET);
    
    // Leitura garantida de 1 bloco de memoria para cada variavel
    if (fread(quantidade, sizeof(int), 1, f) != 1) 
        return -1;
        
    if (fread(deslocamento_dir, sizeof(long), 1, f) != 1) 
        return -1;
        
    return 0;
}

// Escreve o superbloco atualizado no inicio do container
// Retorna 0 se escreveu com sucesso ou -1 em caso de erro
int escreveSuperbloco (FILE *f, int quantidade, long deslocamento_dir) {
    if (!f)
        return -1;

    fseek(f, 0, SEEK_SET);
    fwrite(&quantidade, sizeof(int), 1, f);
    fwrite(&deslocamento_dir, sizeof(long), 1, f);
    
    return 0;
}

// Cria um novo container vazio com o nome especificado
// Retorna 0 se criou com sucesso ou -1 em caso de erro
int gbv_criar (const char *nome_arquivo) {
    FILE *f;
    int quantidade;
    long deslocamento;

    // Tenta criar um novo arquivo binario para leitura e escrita
    f = fopen(nome_arquivo, "w+b");
    if (!f) 
        return -1;
        
    // Inicializa valores do superbloco vazio
    quantidade = 0;
    deslocamento = sizeof(int) + sizeof(long); // o diretorio comeca logo apos o superbloco
    
    escreveSuperbloco(f, quantidade, deslocamento);
    fclose(f);
    
    return 0;
}

// Abre um container existente ou cria um novo se o arquivo nao existir
// Carrega o diretorio de documentos para a memoria RAM (Biblioteca)
// Retorna 0 se abriu/criou com sucesso ou -1 em caso de erro
int gbv_abrir (Biblioteca *bib, const char *nome_arquivo) {
    FILE *f;
    int quantidade;
    long deslocamento_dir;

    // Guarda o nome do container na variavel global para uso no gbv_remover
    strncpy(arquivo_atual, nome_arquivo, MAX_NOME - 1);
    arquivo_atual[MAX_NOME - 1] = '\0';
    
    // Abre o arquivo container
    f = fopen(nome_arquivo, "r+b");
    
    // Se o arquivo nao existe, cria um novo container vazio
    if (!f) {
        if (gbv_criar(nome_arquivo) != 0) 
            return -1;
            
        f = fopen(nome_arquivo, "r+b");
        if (!f) 
            return -1;
    }

    // Le os dados base do superbloco para saber onde buscar o diretorio
    if (leSuperbloco(f, &quantidade, &deslocamento_dir) != 0) {
        fclose(f);
        return -1;
    }

    bib -> quantidade = quantidade;
    
    // Se existem documentos, aloca memoria dinamicamente para o vetor de diretório
    if (quantidade > 0) 
    {
        bib -> documentos = malloc(quantidade * sizeof(Documento));
        if (bib -> documentos) {
            fseek(f, deslocamento_dir, SEEK_SET);
            fread(bib -> documentos, sizeof(Documento), quantidade, f);
        }
    } 
    else 
    {
        bib -> documentos = NULL;
    }

    fclose(f);
    return 0;
}

// Adiciona um novo documento ao container, copiando os dados do arquivo de origem
// Caso o documento ja exista, ele sera substituido (dados antigos serao perdidos)
// Retorna 0 se adicionou com sucesso ou -1 em caso de erro
int gbv_adicionar (Biblioteca *bib, const char *container, const char *nome_documento) {
    FILE *f_entrada, *c;
    int i, quantidade, indice;
    long deslocamento_dir, deslocamento_inicial, tamanho_arquivo, novo_deslocamento_dir;
    char buffer[TAMANHO_BUFFER];
    size_t bytes_lidos;
    Documento *temp;

    // Abre o arquivo de origem (o documento que sera inserido)
    f_entrada = fopen(nome_documento, "rb");
    if (!f_entrada) {
        printf("Erro ao abrir o documento de origem: %s\n", nome_documento);
        return -1;
    }

    // Abre o container principal (biblioteca)
    c = fopen(container, "r+b");
    if (!c) {
        fclose(f_entrada);
        return -1;
    }

    leSuperbloco(c, &quantidade, &deslocamento_dir);

    // Verifica se o documento ja existe na biblioteca (para substituicao)
    indice = -1;
    for (i = 0; i < bib -> quantidade; i++) {
        if (strcmp(bib -> documentos[i].nome, nome_documento) == 0) {
            indice = i; 
            break;
        }
    }

    // O novo arquivo sera apensado exatamente onde comecava o diretorio antigo
    fseek(c, deslocamento_dir, SEEK_SET);
    deslocamento_inicial = deslocamento_dir;
    tamanho_arquivo = 0;

    // Copia os dados em blocos para respeitar o limite rigido de buffers na RAM
    while ((bytes_lidos = fread(buffer, 1, TAMANHO_BUFFER, f_entrada)) > 0) {
        fwrite(buffer, 1, bytes_lidos, c);
        tamanho_arquivo += bytes_lidos;
    }
    fclose(f_entrada);

    // Calcula o novo local do diretorio (logo apos os dados recem inseridos)
    novo_deslocamento_dir = deslocamento_inicial + tamanho_arquivo;

    // Atualiza metadados na memoria RAM (Biblioteca)
    if (indice == -1) 
    {
        // Documento novo: expande o vetor dinamico
        temp = realloc(bib -> documentos, (bib -> quantidade + 1) * sizeof(Documento));
        if (!temp) { 
            fclose(c); 
            return -1; 
        }
        bib -> documentos = temp;
        indice = bib -> quantidade;
        bib -> quantidade++;
    }

    // Grava as novas informacoes no espaco reservado do vetor
    strncpy(bib -> documentos[indice].nome, nome_documento, MAX_NOME - 1);
    bib -> documentos[indice].nome[MAX_NOME - 1] = '\0';
    bib -> documentos[indice].tamanho = tamanho_arquivo;
    bib -> documentos[indice].data = time(NULL);
    bib -> documentos[indice].deslocamento = deslocamento_inicial;

    // Grava o diretorio atualizado de volta no container, no novo deslocamento
    fseek(c, novo_deslocamento_dir, SEEK_SET);
    fwrite(bib -> documentos, sizeof(Documento), bib -> quantidade, c);

    // Atualiza o superbloco com o novo total de arquivos e a nova posicao do diretorio
    escreveSuperbloco(c, bib -> quantidade, novo_deslocamento_dir);
    fclose(c);
    
    return 0;
}

// Remove um documento do container, eliminando sua entrada do diretorio e liberando espaco na RAM
// Retorna 0 se removeu com sucesso ou -1 em caso de erro
int gbv_remover (Biblioteca *bib, const char *nome_documento) {
    int i, quantidade, indice;
    long deslocamento_dir;
    FILE *c;
    Documento *temp;

    // Busca o documento pelo nome no diretorio carregado na memoria
    indice = -1;
    for (i = 0; i < bib -> quantidade; i++) {
        if (strcmp(bib -> documentos[i].nome, nome_documento) == 0) {
            indice = i; 
            break;
        }
    }
    
    // Se o documento nao existe, cancela a operacao
    if (indice == -1) {
        printf("Documento não encontrado na biblioteca.\n");
        return -1;
    }

    // Remove logicamente o documento deslocando os itens do vetor sobre ele
    for (i = indice; i < bib -> quantidade - 1; i++) {
        bib -> documentos[i] = bib -> documentos[i+1];
    }
    bib -> quantidade--;

    // Realoca o vetor para liberar o espaco ou zera caso esteva vazio
    if (bib -> quantidade > 0) 
    {
        temp = realloc(bib -> documentos, bib -> quantidade * sizeof(Documento));
        if (temp) 
            bib -> documentos = temp;
    } 
    else 
    {
        free(bib -> documentos);
        bib -> documentos = NULL;
    }

    // Persiste a remocao no disco acessando o container armazenado na variavel global
    c = fopen(arquivo_atual, "r+b");
    if (c) {
        leSuperbloco(c, &quantidade, &deslocamento_dir);
        
        // Reescreve o diretorio reduzido exatamente no mesmo offset que estava antes
        fseek(c, deslocamento_dir, SEEK_SET);
        if (bib -> quantidade > 0) {
            fwrite(bib -> documentos, sizeof(Documento), bib -> quantidade, c);
        }
        
        escreveSuperbloco(c, bib -> quantidade, deslocamento_dir);
        fclose(c);
    }
    return 0;
}

// Lista os documentos presentes na biblioteca, mostrando seus metadados formatados
// Retorna 0 se listou com sucesso ou -1 em caso de erro
int gbv_listar (const Biblioteca *bib) {
    int i;
    char str_data[64];

    if (!bib) 
        return -1;

    printf("%-30s %-15s %-25s %-15s\n", "Nome", "Tamanho (B)", "Data Insercao", "Deslocamento");
    printf("--------------------------------------------------------------------------------------\n");
    
    // Varre o vetor da biblioteca (ja presente na memoria) imprimindo os metadados
    for (i = 0; i < bib -> quantidade; i++) {
        formatar_data(bib -> documentos[i].data, str_data, sizeof(str_data));
        printf("%-30s %-15ld %-25s %-15ld\n",
               bib -> documentos[i].nome,
               bib -> documentos[i].tamanho,
               str_data,
               bib -> documentos[i].deslocamento);
    }
    
    return 0;
}

// Permite visualizar o conteudo de um documento presente na biblioteca, lendo diretamente do container
// Implementa um sistema de paginacao para navegar por arquivos maiores que o buffer
// Retorna 0 se visualizou com sucesso ou -1 em caso de erro
int gbv_visualizar (const Biblioteca *bib, const char *nome_documento) {
    int i, indice;
    long deslocamento_doc, tamanho_doc, posicao_atual, bytes_para_ler;
    FILE *c;
    char buffer[TAMANHO_BUFFER];
    char comando[10];
    size_t bytes_lidos;

    if (!bib || !nome_documento) 
        return -1;

    // Busca o arquivo selecionado para visualizacao
    indice = -1;
    for (i = 0; i < bib -> quantidade; i++) {
        if (strcmp(bib -> documentos[i].nome, nome_documento) == 0) {
            indice = i; 
            break;
        }
    }
    
    if (indice == -1) {
        printf("Documento não encontrado.\n");
        return -1;
    }

    // Abre o container principal como leitura pura
    c = fopen(arquivo_atual, "rb");
    if (!c) 
        return -1;

    deslocamento_doc = bib -> documentos[indice].deslocamento;
    tamanho_doc = bib -> documentos[indice].tamanho;
    posicao_atual = 0;

    // Loop de controle de paginacao
    while (1) {
        fseek(c, deslocamento_doc + posicao_atual, SEEK_SET);
        
        bytes_para_ler = TAMANHO_BUFFER;
        
        // Garante que a leitura nao va ultrapassar o limite (tamanho total) do documento
        if (posicao_atual + TAMANHO_BUFFER > tamanho_doc) 
            bytes_para_ler = tamanho_doc - posicao_atual;

        // Se tem o que ler, imprime na tela
        if (bytes_para_ler > 0) 
        {
            bytes_lidos = fread(buffer, 1, bytes_para_ler, c);
            printf("\n--- BLOCO (Byte %ld ao %ld de %ld) ---\n", posicao_atual, posicao_atual + bytes_lidos, tamanho_doc);
            
            // O fwrite no stdout previne bugs com strings sem nulo terminador '\0'
            fwrite(buffer, 1, bytes_lidos, stdout); 
            printf("\n----------------------------------------\n");
        } 
        else 
        {
            printf("\n--- FIM DO DOCUMENTO ---\n");
        }

        // Aguarda entrada do usuario
        printf("Acao (n=proximo, p=anterior, q=sair): ");
        if (!fgets(comando, sizeof(comando), stdin)) 
            break;

        if (comando[0] == 'q') 
        {
            break;
        } 
        else if (comando[0] == 'n') 
        {
            // Avanca o ponteiro logico do documento se nao tiver atingido o fim
            if (posicao_atual + TAMANHO_BUFFER < tamanho_doc) 
                posicao_atual += TAMANHO_BUFFER;
            else 
                printf("Você ja esta no final do documento.\n");
                
        } 
        else if (comando[0] == 'p') 
        {
            // Retrocede o ponteiro logico, protegendo para nao ficar negativo
            if (posicao_atual - TAMANHO_BUFFER >= 0) 
                posicao_atual -= TAMANHO_BUFFER;
            else {
                posicao_atual = 0;
                printf("Você ja esta no inicio do documento.\n");
            }
        }
    }
    
    fclose(c);
    return 0;
}

// Compara por nome usando strcmp
static int cmpNome (const void *a, const void *b) {
    return strcmp(((Documento*)a) -> nome, ((Documento*)b) -> nome);
}

// Compara por data usando a diferenca de time_t 
// Retorna positivo se a > b, negativo se a < b e zero se iguais
static int cmpData (const void *a, const void *b) {
    time_t t1 = ((Documento*)a) -> data;
    time_t t2 = ((Documento*)b) -> data;
    return (t1 > t2) - (t1 < t2);
}

// Compara por tamanho usando a diferenca de long
// Retorna positivo se a > b, negativo se a < b e zero se iguais
static int cmpTamanho (const void *a, const void *b) {
    long s1 = ((Documento*)a) -> tamanho;
    long s2 = ((Documento*)b) -> tamanho;
    return (s1 > s2) - (s1 < s2);
}

// Permite reordenar os documentos da biblioteca com base em um criterio escolhido pelo usuario (nome, data ou tamanho)
// Retorna 0 se reordenou com sucesso ou -1 em caso de erro
int gbv_ordenar (Biblioteca *bib, const char *container, const char *criterio) {
    FILE *c;
    int quantidade;
    long deslocamento_dir;

    // Define qual callback de ordenacao usar com base no criterio escolhido pelo usuario
    if (strcmp(criterio, "nome") == 0) 
    {
        qsort(bib -> documentos, bib -> quantidade, sizeof(Documento), cmpNome);
    } 
    else if (strcmp(criterio, "data") == 0) 
    {
        qsort(bib -> documentos, bib -> quantidade, sizeof(Documento), cmpData);
    } 
    else if (strcmp(criterio, "tamanho") == 0) 
    {
        qsort(bib -> documentos, bib -> quantidade, sizeof(Documento), cmpTamanho);
    } 
    else 
    {
        printf("Criterio invalido. Use 'nome', 'data' ou 'tamanho'.\n");
        return -1;
    }

    // Persiste a nova ordem reescrevendo o vetor do diretorio no arquivo
    c = fopen(container, "r+b");
    if (!c) 
        return -1;
        
    leSuperbloco(c, &quantidade, &deslocamento_dir);

    fseek(c, deslocamento_dir, SEEK_SET);
    fwrite(bib -> documentos, sizeof(Documento), bib -> quantidade, c);
    
    fclose(c);
    
    printf("Biblioteca reordenada por '%s' com sucesso.\n", criterio);
    
    return 0;
}