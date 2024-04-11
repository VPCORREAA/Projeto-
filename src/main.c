#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[4](tarefas, &pos);
    if(erro != OK)
        pos = 0;

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if(scanf("%d", &opcao) != 1) {
            printf("Entrada inválida\n");
            continue;
        }

        if(opcao < 0 || opcao > 3) {
            printf("Opcao invalida\n");
            continue;
        }
        if(opcao == 0) {
            printf("Sair...\n");
            break;
        }

        fs[opcao - 1](tarefas, &pos);

    } while(opcao != 0);

    fs[3](tarefas, &pos);

    return 0; // Adicionado o retorno da função main
}
