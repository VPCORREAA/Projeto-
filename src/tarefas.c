#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    printf("Entre com a prioridade (1 a 10): ");
    if(scanf("%d", &tarefas[*pos].prioridade) != 1) {
        clearBuffer();
        return ENTRADA_INVALIDA;
    }
    clearBuffer();

    if(tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10)
        return PRIORIDADE_INVALIDA;

    printf("Entre com a categoria: ");
    if(fgets(tarefas[*pos].categoria, TAM_CATEGORIA, stdin) == NULL) {
        return ENTRADA_INVALIDA;
    }
    strtok(tarefas[*pos].categoria, "\n"); // Remove a quebra de linha

    printf("Entre com a descricao: ");
    if(fgets(tarefas[*pos].descricao, TAM_DESCRICAO, stdin) == NULL) {
        return ENTRADA_INVALIDA;
    }
    strtok(tarefas[*pos].descricao, "\n"); // Remove a quebra de linha

    *pos = *pos + 1;

    return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    if(scanf("%d", &pos_deletar) != 1) {
        clearBuffer();
        return ENTRADA_INVALIDA;
    }
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0) {
        printf("Nenhuma tarefa encontrada.\n");
        return SEM_TAREFAS;
    }

    char categoria[TAM_CATEGORIA];
    printf("Entre com a categoria (deixe vazio para listar todas as categorias): ");
    if(fgets(categoria, TAM_CATEGORIA, stdin) == NULL) {
        printf("Erro ao ler a entrada.\n");
        return ENTRADA_INVALIDA;
    }
    strtok(categoria, "\n"); // Remove a quebra de linha

    printf("Categoria digitada: %s\n", categoria); // Mensagem de depuração

    int encontradas = 0;
    for(int i = 0; i < *pos; i++){
        if(categoria[0] == '\0' || strcmp(tarefas[i].categoria, categoria) == 0) {
            encontradas++;
            printf("Pos: %d\t", i+1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
        }
    }

    if(encontradas == 0) {
        printf("Nenhuma tarefa encontrada para a categoria digitada.\n");
        return NENHUMA_ENCONTRADA;
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    char nome_arquivo[100];
    printf("Entre com o nome do arquivo para salvar: ");
    if(scanf("%s", nome_arquivo) != 1) {
        return ENTRADA_INVALIDA;
    }

    FILE *f = fopen(nome_arquivo, "w");
    if(f == NULL)
        return ABRIR;

    for(int i = 0; i < *pos; i++) {
        fprintf(f, "%d;%s;%s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
    }

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    char nome_arquivo[100];
    printf("Entre com o nome do arquivo para carregar: ");
    if(scanf("%s", nome_arquivo) != 1) {
        return ENTRADA_INVALIDA;
    }

    FILE *f = fopen(nome_arquivo, "r");
    if(f == NULL)
        return ABRIR;

    *pos = 0;
    while(fscanf(f, "%d;%99[^;];%299[^\n]", &tarefas[*pos].prioridade, tarefas[*pos].categoria, tarefas[*pos].descricao) == 3) {
        (*pos)++;
        if(*pos >= TOTAL)
            break;
    }

    if(fclose(f))
        return FECHAR;

    return OK;
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
