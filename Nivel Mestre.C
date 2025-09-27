#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

typedef enum {
    NAO_ORDENADO,
    ORDENADO_NOME,
    ORDENADO_TIPO,
    ORDENADO_PRIORIDADE
} EstadoOrdenacao;

Componente mochila[MAX_COMPONENTES];
int total = 0;
EstadoOrdenacao estadoAtual = NAO_ORDENADO;

// Função para exibir todos os componentes
void mostrarComponentes() {
    printf("\n--- Componentes da Mochila ---\n");
    for (int i = 0; i < total; i++) {
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].prioridade);
    }
}

// Função para adicionar componente
void adicionarComponente() {
    if (total >= MAX_COMPONENTES) {
        printf("\nMochila cheia!\n");
        return;
    }

    Componente novo;
    printf("\nDigite o nome do componente: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Digite o tipo do componente: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    do {
        printf("Digite a prioridade (1 a 5): ");
        scanf("%d", &novo.prioridade);
        getchar();
    } while (novo.prioridade < 1 || novo.prioridade > 5);

    mochila[total++] = novo;
    estadoAtual = NAO_ORDENADO;
    printf("\nComponente adicionado com sucesso!\n");
}

// Bubble Sort por nome
int bubbleSortNome() {
    int comparacoes = 0;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Componente temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    estadoAtual = ORDENADO_NOME;
    return comparacoes;
}

// Insertion Sort por tipo
int insertionSortTipo() {
    int comparacoes = 0;
    for (int i = 1; i < total; i++) {
        Componente chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }
        mochila[j + 1] = chave;
        comparacoes++;
    }
    estadoAtual = ORDENADO_TIPO;
    return comparacoes;
}

// Selection Sort por prioridade
int selectionSortPrioridade() {
    int comparacoes = 0;
    for (int i = 0; i < total - 1; i++) {
        int min = i;
        for (int j = i + 1; j < total; j++) {
            comparacoes++;
            if (mochila[j].prioridade < mochila[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = mochila[i];
            mochila[i] = mochila[min];
            mochila[min] = temp;
        }
    }
    estadoAtual = ORDENADO_PRIORIDADE;
    return comparacoes;
}

// Busca binária por nome
void buscaBinariaPorNome() {
    if (estadoAtual != ORDENADO_NOME) {
        printf("\nA mochila precisa estar ordenada por nome para realizar busca binária.\n");
        return;
    }

    char chave[30];
    printf("\nDigite o nome do componente a buscar: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int inicio = 0, fim = total - 1, comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, chave);
        if (cmp == 0) {
            printf("\nComponente encontrado:\nNome: %s\nTipo: %s\nPrioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].prioridade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\nComponente não encontrado. Comparações realizadas: %d\n", comparacoes);
}

// Medir tempo de execução
void medirTempo(int (*algoritmo)(), const char* nomeAlgoritmo) {
    clock_t inicio = clock();
    int comparacoes = algoritmo();
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nOrdenação concluída com %d comparações.\n", comparacoes);
    printf("Tempo de execução (%s): %.6f segundos\n", nomeAlgoritmo, tempo);
    mostrarComponentes();
}

// Menu principal
int main() {
    int opcao;

    do {
        printf("\n===== Desafio Código da Ilha – Nível Mestre =====\n");
        printf("1. Adicionar componente\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente por nome (Binária)\n");
        printf("6. Mostrar componentes\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do scanf

        switch (opcao) {
            case 1: adicionarComponente(); break;
            case 2: medirTempo(bubbleSortNome, "Bubble Sort"); break;
            case 3: medirTempo(insertionSortTipo, "Insertion Sort"); break;
            case 4: medirTempo(selectionSortPrioridade, "Selection Sort"); break;
            case 5: buscaBinariaPorNome(); break;
            case 6: mostrarComponentes(); break;
            case 0: printf("\nEncerrando o sistema...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}