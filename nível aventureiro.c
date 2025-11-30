#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20  // capacidade máxima da mochila por vetor

// ======================================================
// STRUCTS
// ======================================================

// Struct base do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* prox;
} No;

// ======================================================
// VARIÁVEIS GLOBAIS PARA CONTAR COMPARAÇÕES
// ======================================================
int compSequencial = 0;
int compBinaria = 0;

// ======================================================
// FUNÇÕES PARA A MOCHILA COM VETOR
// ======================================================

// Inserir item no vetor
void inserirItemVetor(Item vet[], int *n) {
    if (*n >= MAX) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\n--- Inserir Item (Vetor) ---\n");
    printf("Nome: ");
    scanf(" %29[^\n]", vet[*n].nome);
    printf("Tipo: ");
    scanf(" %19[^\n]", vet[*n].tipo);
    printf("Quantidade: ");
    scanf("%d", &vet[*n].quantidade);

    (*n)++;
    printf("Item inserido!\n");
}

// Remover item do vetor
void removerItemVetor(Item vet[], int *n) {
    char nome[30];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %29[^\n]", nome);

    for (int i = 0; i < *n; i++) {
        if (strcmp(vet[i].nome, nome) == 0) {
            vet[i] = vet[*n - 1];
            (*n)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

// Listar vetor
void listarItensVetor(Item vet[], int n) {
    printf("\n--- Itens (Vetor) ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d) %s | %s | x%d\n", i + 1, vet[i].nome, vet[i].tipo, vet[i].quantidade);
    }
    if (n == 0) printf("Vazio!\n");
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item vet[], int n, char *nome) {
    compSequencial = 0;
    for (int i = 0; i < n; i++) {
        compSequencial++;
        if (strcmp(vet[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordenar vetor por nome
void ordenarVetor(Item vet[], int n) {
    printf("\nOrdenando vetor...\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                Item temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado!\n");
}

// Busca binária
int buscarBinariaVetor(Item vet[], int n, char *nome) {
    int inicio = 0, fim = n - 1;
    compBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        compBinaria++;

        int cmp = strcmp(nome, vet[meio].nome);

        if (cmp == 0) return meio;
        if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}

// ======================================================
// FUNÇÕES PARA A MOCHILA COM LISTA ENCADEADA
// ======================================================

// Inserir na lista
void inserirItemLista(No **lista) {
    No *novo = (No*) malloc(sizeof(No));

    printf("\n--- Inserir Item (Lista) ---\n");
    printf("Nome: ");
    scanf(" %29[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %19[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->prox = *lista;
    *lista = novo;

    printf("Item inserido!\n");
}

// Remover da lista
void removerItemLista(No **lista) {
    char nome[30];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %29[^\n]", nome);

    No *atual = *lista;
    No *ant = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (ant == NULL)
                *lista = atual->prox;
            else
                ant->prox = atual->prox;

            free(atual);
            printf("Item removido!\n");
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
    printf("Item não encontrado!\n");
}

// Listar lista
void listarItensLista(No *lista) {
    printf("\n--- Itens (Lista Encadeada) ---\n");
    if (lista == NULL) {
        printf("Vazio!\n");
        return;
    }
    while (lista != NULL) {
        printf("%s | %s | x%d\n", lista->dados.nome, lista->dados.tipo, lista->dados.quantidade);
        lista = lista->prox;
    }
}

// Busca sequencial na lista encadeada
int buscarItemLista(No *lista, char *nome) {
    compSequencial = 0;
    while (lista != NULL) {
        compSequencial++;
        if (strcmp(lista->dados.nome, nome) == 0) {
            return 1;
        }
        lista = lista->prox;
    }
    return 0;
}

// ======================================================
// MENU PRINCIPAL
// ======================================================
int main() {
    Item mochilaVet[MAX];
    int n = 0;

    No *mochilaLista = NULL;

    int opcao, estr;
    char nomeBusca[30];

    do {
        printf("\n========= SISTEMA DE INVENTÁRIO =========\n");
        printf("1 - Usar mochila com VETOR\n");
        printf("2 - Usar mochila com LISTA ENCADEADA\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &estr);

        if (estr == 1) {
            do {
                printf("\n--- Mochila (VETOR) ---\n");
                printf("1 - Inserir\n");
                printf("2 - Remover\n");
                printf("3 - Listar\n");
                printf("4 - Busca Sequencial\n");
                printf("5 - Ordenar\n");
                printf("6 - Busca Binária\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        inserirItemVetor(mochilaVet, &n);
                        break;

                    case 2:
                        removerItemVetor(mochilaVet, &n);
                        break;

                    case 3:
                        listarItensVetor(mochilaVet, n);
                        break;

                    case 4:
                        printf("\nNome para buscar: ");
                        scanf(" %29[^\n]", nomeBusca);
                        if (buscarSequencialVetor(mochilaVet, n, nomeBusca) != -1)
                            printf("Encontrado!\n");
                        else
                            printf("Não encontrado!\n");

                        printf("Comparações (sequencial): %d\n", compSequencial);
                        break;

                    case 5:
                        ordenarVetor(mochilaVet, n);
                        break;

                    case 6:
                        printf("\nNome para buscar: ");
                        scanf(" %29[^\n]", nomeBusca);
                        if (buscarBinariaVetor(mochilaVet, n, nomeBusca) != -1)
                            printf("Encontrado!\n");
                        else
                            printf("Não encontrado!\n");

                        printf("Comparações (binária): %d\n", compBinaria);
                        break;
                }

            } while (opcao != 0);

        } else if (estr == 2) {
            do {
                printf("\n--- Mochila (LISTA) ---\n");
                printf("1 - Inserir\n");
                printf("2 - Remover\n");
                printf("3 - Listar\n");
                printf("4 - Buscar\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        inserirItemLista(&mochilaLista);
                        break;

                    case 2:
                        removerItemLista(&mochilaLista);
                        break;

                    case 3:
                        listarItensLista(mochilaLista);
                        break;

                    case 4:
                        printf("\nNome para buscar: ");
                        scanf(" %29[^\n]", nomeBusca);
                        if (buscarItemLista(mochilaLista, nomeBusca))
                            printf("Encontrado!\n");
                        else
                            printf("Não encontrado!\n");

                        printf("Comparações (sequencial - lista): %d\n", compSequencial);
                        break;
                }

            } while (opcao != 0);
        }

    } while (estr != 0);

    printf("\nSistema encerrado!\n");
    return 0;
}