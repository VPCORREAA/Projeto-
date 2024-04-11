#define TOTAL 100
#define TAM_CATEGORIA 100
#define TAM_DESCRICAO 300

typedef struct {
    int prioridade;
    char descricao[TAM_DESCRICAO];
    char categoria[TAM_CATEGORIA];
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER, PRIORIDADE_INVALIDA, NENHUMA_ENCONTRADA, ENTRADA_INVALIDA} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);

void clearBuffer();
