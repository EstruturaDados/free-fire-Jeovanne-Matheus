#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct do ite 
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor de itens
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// Lista encadeada
No* mochilaLista = NULL;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Funções para vetor
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novo;
    printf("\nNome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalVetor++] = novo;
    printf("\nItem inserido com sucesso!\n");
}

void removerItemVetor() {
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalVetor--;
            printf("\nItem removido!\n");
            return;
        }
    }
    printf("\nItem não encontrado.\n");
}

void listarItensVetor() {
    if (totalVetor == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\nItens no vetor:\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void buscarSequencialVetor() {
    char nome[30];
    comparacoesSequencial = 0;

    printf("\nNome do item a buscar: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\nItem encontrado:\nNome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            return;
        }
    }
    printf("\nItem não encontrado. Comparações: %d\n", comparacoesSequencial);
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome.\n");
}

void buscarBinariaVetor() {
    char nome[30];
    comparacoesBinaria = 0;

    printf("\nNome do item a buscar (binária): ");
    scanf(" %[^\n]", nome);

    int inicio = 0, fim = totalVetor - 1;
    while (inicio <= fim) {
        comparacoesBinaria++;
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0) {
            printf("\nItem encontrado:\nNome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações realizadas: %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\nItem não encontrado. Comparações: %d\n", comparacoesBinaria);
}

// Funções para lista encadeada
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return;

    printf("\nNome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;

    printf("\nItem inserido na lista!\n");
}

void removerItemLista() {
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf(" %[^\n]", nome);

    No *atual = mochilaLista, *anterior = NULL;
    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                mochilaLista = atual->proximo;
            free(atual);
            printf("\nItem removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("\nItem não encontrado na lista.\n");
}

void listarItensLista() {
    if (!mochilaLista) {
        printf("\nLista vazia.\n");
        return;
    }

    printf("\nItens na lista:\n");
    No* atual = mochilaLista;
    while (atual) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    char nome[30];
    comparacoesSequencial = 0;

    printf("\nNome do item a buscar na lista: ");
    scanf(" %[^\n]", nome);

    No* atual = mochilaLista;
    while (atual) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\nItem encontrado:\nNome: %s\nTipo: %s\nQuantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }
    printf("\nItem não encontrado. Comparações: %d\n", comparacoesSequencial);
}

// Menu principal
int main() {
    int estrutura, opcao;

    do {
        printf("\nEscolha a estrutura:\n1. Vetor\n2. Lista Encadeada\n0. Sair\nOpção: ");
        scanf("%d", &estrutura);

        switch (estrutura) {
            case 1:
                do {
                    printf("\n--- Mochila com Vetor ---\n");
                    printf("1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n5. Ordenar\n6. Buscar Binária\n0. Voltar\nOpção: ");
                    scanf("%d", &opcao);
                    switch (opcao) {
                        case 1: inserirItemVetor(); break;
                        case 2: removerItemVetor(); break;
                        case 3: listarItensVetor(); break;
                        case 4: buscarSequencialVetor(); break;
                        case 5: ordenarVetor(); break;
                        case 6: buscarBinariaVetor(); break;
                    }
                } while (opcao != 0);
                break;

            case 2:
                                do {
                    printf("\n--- Mochila com Lista Encadeada ---\n");
                    printf("1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n0. Voltar\nOpção: ");
                    scanf("%d", &opcao);
                    switch (opcao) {
                        case 1: inserirItemLista(); break;
                        case 2: removerItemLista(); break;
                        case 3: listarItensLista(); break;
                        case 4: buscarSequencialLista(); break;
                    }
                } while (opcao != 0);
                break;

            case 0:
                printf("\nEncerrando o sistema de inventário...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (estrutura != 0);

    return 0;
}