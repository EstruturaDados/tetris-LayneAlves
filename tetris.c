#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Nível Mestre


// Definição da struct para representar uma peça
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único da peça
} Peca;

// Constantes para tamanhos das estruturas
#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// Variável global para o próximo ID único
int proximoId = 0;

// Função para gerar uma nova peça aleatoriamente
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    novaPeca.nome = tipos[rand() % 4];  // Escolhe um tipo aleatório
    novaPeca.id = proximoId++;           // Atribui ID único e incrementa
    return novaPeca;
}

// Estrutura para a fila circular
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int front;  // Índice do início da fila
    int rear;   // Índice do fim da fila
    int tamanho; // Número atual de elementos
} FilaCircular;

// Função para inicializar a fila
void inicializarFila(FilaCircular *fila) {
    fila->front = 0;
    fila->rear = -1;
    fila->tamanho = 0;
    // Preenche a fila com 5 peças iniciais
    for (int i = 0; i < TAMANHO_FILA; i++) {
        fila->pecas[i] = gerarPeca();
        fila->rear = (fila->rear + 1) % TAMANHO_FILA;
        fila->tamanho++;
    }
}

// Função para verificar se a fila está vazia
int filaVazia(FilaCircular *fila) {
    return fila->tamanho == 0;
}

// Função para verificar se a fila está cheia
int filaCheia(FilaCircular *fila) {
    return fila->tamanho == TAMANHO_FILA;
}

// Função para enfileirar uma peça na fila
void enqueue(FilaCircular *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    fila->rear = (fila->rear + 1) % TAMANHO_FILA;
    fila->pecas[fila->rear] = peca;
    fila->tamanho++;
}

// Função para desenfileirar uma peça da fila
Peca dequeue(FilaCircular *fila) {
    if (filaVazia(fila)) {
        printf("Erro: Fila vazia!\n");
        Peca erro = {'\0', -1};
        return erro;
    }
    Peca peca = fila->pecas[fila->front];
    fila->front = (fila->front + 1) % TAMANHO_FILA;
    fila->tamanho--;
    return peca;
}

// Função para obter a peça da frente da fila sem removê-la
Peca frenteFila(FilaCircular *fila) {
    if (filaVazia(fila)) {
        Peca erro = {'\0', -1};
        return erro;
    }
    return fila->pecas[fila->front];
}

// Estrutura para a pilha
typedef struct {
    Peca pecas[TAMANHO_PILHA];
    int topo;  // Índice do topo da pilha (-1 se vazia)
} Pilha;

// Função para inicializar a pilha
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

// Função para verificar se a pilha está cheia
int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAMANHO_PILHA - 1;
}

// Função para empilhar uma peça
void push(Pilha *pilha, Peca peca) {
    if (pilhaCheia(pilha)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    pilha->topo++;
    pilha->pecas[pilha->topo] = peca;
}

// Função para desempilhar uma peça
Peca pop(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Erro: Pilha vazia!\n");
        Peca erro = {'\0', -1};
        return erro;
    }
    Peca peca = pilha->pecas[pilha->topo];
    pilha->topo--;
    return peca;
}

// Função para obter o topo da pilha sem removê-lo
Peca topoPilha(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        Peca erro = {'\0', -1};
        return erro;
    }
    return pilha->pecas[pilha->topo];
}

// Função para exibir o estado atual da fila e pilha
void exibirEstado(FilaCircular *fila, Pilha *pilha) {
    printf("\nEstado atual:\n");
    printf("Fila de peças\t");
    if (filaVazia(fila)) {
        printf("(Vazia)");
    } else {
        int i = fila->front;
        for (int count = 0; count < fila->tamanho; count++) {
            printf("[%c %d] ", fila->pecas[i].nome, fila->pecas[i].id);
            i = (i + 1) % TAMANHO_FILA;
        }
    }
    printf("\nPilha de reserva\t(Topo -> Base): ");
    if (pilhaVazia(pilha)) {
        printf("(Vazia)");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->pecas[i].nome, pilha->pecas[i].id);
        }
    }
    printf("\n\n");
}

// Função para trocar a peça da frente da fila com o topo da pilha
void trocarFrenteComTopo(FilaCircular *fila, Pilha *pilha) {
    if (filaVazia(fila)) {
        printf("Erro: Fila vazia, não é possível trocar.\n");
        return;
    }
    if (pilhaVazia(pilha)) {
        printf("Erro: Pilha vazia, não é possível trocar.\n");
        return;
    }
    // Troca diretamente
    Peca temp = frenteFila(fila);
    fila->pecas[fila->front] = topoPilha(pilha);
    pilha->pecas[pilha->topo] = temp;
    printf("Troca realizada: Peça da frente da fila [%c %d] com topo da pilha [%c %d].\n",
           temp.nome, temp.id, fila->pecas[fila->front].nome, fila->pecas[fila->front].id);
}

// Função para trocar os 3 primeiros da fila com as 3 peças da pilha
void trocarTresPrimeirosComTresPilha(FilaCircular *fila, Pilha *pilha) {
    if (pilha->topo + 1 != TAMANHO_PILHA) {
        printf("Erro: Pilha deve ter exatamente 3 peças.\n");
        return;
    }
    if (fila->tamanho < 3) {
        printf("Erro: Fila deve ter pelo menos 3 peças.\n");
        return;
    }
    // Troca os 3 primeiros da fila com os 3 da pilha
    // Pilha: topo, topo-1, topo-2
    // Fila: front, front+1, front+2
    Peca temp[3];
    int idxFila = fila->front;
    for (int i = 0; i < 3; i++) {
        temp[i] = fila->pecas[idxFila];
        idxFila = (idxFila + 1) % TAMANHO_FILA;
    }
    int idxPilha = pilha->topo;
    for (int i = 0; i < 3; i++) {
        fila->pecas[(fila->front + i) % TAMANHO_FILA] = pilha->pecas[idxPilha];
        pilha->pecas[idxPilha] = temp[i];
        idxPilha--;
    }
    printf("Troca realizada: 3 primeiros da fila com as 3 da pilha.\n");
}

// Função principal
int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios

    FilaCircular fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        printf("Opções de Ação:\n");
        printf("Código\tAção\n");
        printf("1\tJogar peça\n");
        printf("2\tReservar peça\n");
        printf("3\tUsar peça reservada\n");
        printf("4\tTrocar peça da frente com topo da pilha\n");
        printf("5\tTrocar 3 primeiros da fila com os 3 da pilha\n");
        printf("0\tSair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {  // Jogar peça
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                    // Gera nova peça e adiciona ao final da fila
                    Peca nova = gerarPeca();
                    enqueue(&fila, nova);
                }
                break;
            }
            case 2: {  // Reservar peça
                if (!pilhaCheia(&pilha)) {
                    Peca reservada = dequeue(&fila);
                    if (reservada.id != -1) {
                        push(&pilha, reservada);
                        printf("Peça reservada: [%c %d]\n", reservada.nome, reservada.id);
                        // Gera nova peça e adiciona ao final da fila
                        Peca nova = gerarPeca();
                        enqueue(&fila, nova);
                    }
                } else {
                    printf("Erro: Pilha de reserva cheia!\n");
                }
                break;
            }
            case 3: {  // Usar peça reservada
                Peca usada = pop(&pilha);
                if (usada.id != -1) {
                    printf("Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
                }
                break;
            }
            case 4: {  // Trocar peça da frente com topo da pilha
                trocarFrenteComTopo(&fila, &pilha);
                break;
            }
            case 5: {  // Trocar 3 primeiros da fila com os 3 da pilha
                trocarTresPrimeirosComTresPilha(&fila, &pilha);
                break;
            }
            case 0: {
                printf("Saindo do programa...\n");
                break;
            }
            default: {
                printf("Opção inválida! Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}
