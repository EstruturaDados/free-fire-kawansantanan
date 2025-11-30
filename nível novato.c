#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10   // capacidade máxima da mochila

// ------------------------------------------------------
// STRUCT DO ITEM
// ------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ------------------------------------------------------
// CADASTRAR ITEM
// ------------------------------------------------------
void inserirItem(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\n--- Cadastro de Item ---\n");
    printf("Digite o nome do item: ");
    scanf(" %29[^\n]", novo.nome);

    printf("Digite o tipo do item (arma, munição, cura...): ");
    scanf(" %19[^\n]", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*numItens] = novo;
    (*numItens)++;

    printf("\nItem cadastrado com sucesso!\n");
}

// ------------------------------------------------------
// REMOVER ITEM PELO NOME
// ------------------------------------------------------
void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("\nA mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // sobrescreve o item removido com o último da lista
            mochila[i] = mochila[*numItens - 1];
            (*numItens)--;

            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem não encontrado na mochila.\n");
}

// ------------------------------------------------------
// LISTAR ITENS
// ------------------------------------------------------
void listarItens(Item mochila[], int numItens) {
    printf("\n--- Itens na Mochila ---\n");

    if (numItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < numItens; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// ------------------------------------------------------
// BUSCA SEQUENCIAL POR NOME
// ------------------------------------------------------
void buscarItem(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem não encontrado.\n");
}

// ------------------------------------------------------
// MENU PRINCIPAL
// ------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0;
    int opcao;

    do {
        printf("\n========= Sistema de Inventário =========\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
