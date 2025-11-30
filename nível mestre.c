#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ------------------------------
// STRUCT PRINCIPAL DO DESAFIO
// ------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ------------------------------
// VARIÁVEIS GLOBAIS
// ------------------------------
int comparacoes = 0;

// ------------------------------
// FUNÇÃO PARA LISTAR COMPONENTES
// ------------------------------
void mostrarComponentes(Componente v[], int n) {
    printf("\n===== COMPONENTES =====\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("=======================\n");
}

// ------------------------------
// BUBBLE SORT — ordenar por nome
// ------------------------------
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
}

// ------------------------------
// INSERTION SORT — ordenar por tipo
// ------------------------------
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

// ------------------------------
// SELECTION SORT — ordenar por prioridade
// ------------------------------
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }

        if (min != i) {
            Componente tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }
}

// ------------------------------
// BUSCA BINÁRIA POR NOME
// ------------------------------
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n - 1;
    comparacoes = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        comparacoes++;
        int cmp = strcmp(chave, v[meio].nome);

        if (cmp == 0) return meio;
        if (cmp > 0) ini = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// ------------------------------
// MEDIR TEMPO DE EXECUÇÃO
// ------------------------------
double medirTempo(void (*funcao)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    funcao(v, n);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// ------------------------------
// PROGRAMA PRINCIPAL
// ------------------------------
int main() {
    Componente componentes[MAX];
    int qtd = 0;
    int opcao;

    while (1) {
        printf("\n========= MENU PRINCIPAL =========\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar por NOME (Bubble Sort)\n");
        printf("4 - Ordenar por TIPO (Insertion Sort)\n");
        printf("5 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6 - Busca binária por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 0) break;

        switch (opcao) {

        case 1: {
            if (qtd >= MAX) {
                printf("Limite máximo atingido!\n");
                break;
            }
            printf("Nome do componente: ");
            fgets(componentes[qtd].nome, 30, stdin);
            componentes[qtd].nome[strcspn(componentes[qtd].nome, "\n")] = 0;

            printf("Tipo: ");
            fgets(componentes[qtd].tipo, 20, stdin);
            componentes[qtd].tipo[strcspn(componentes[qtd].tipo, "\n")] = 0;

            printf("Prioridade (1 a 10): ");
            scanf("%d", &componentes[qtd].prioridade);
            getchar();

            qtd++;
            break;
        }

        case 2:
            mostrarComponentes(componentes, qtd);
            break;

        case 3: {
            double tempo = medirTempo(bubbleSortNome, componentes, qtd);
            printf("\nBubble Sort concluído!\n");
            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            break;
        }

        case 4: {
            double tempo = medirTempo(insertionSortTipo, componentes, qtd);
            printf("\nInsertion Sort concluído!\n");
            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            break;
        }

        case 5: {
            double tempo = medirTempo(selectionSortPrioridade, componentes, qtd);
            printf("\nSelection Sort concluído!\n");
            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            break;
        }

        case 6: {
            char chave[30];
            printf("Nome do componente a buscar: ");
            fgets(chave, 30, stdin);
            chave[strcspn(chave, "\n")] = 0;

            int pos = buscaBinariaPorNome(componentes, qtd, chave);

            if (pos >= 0) {
                printf("\nComponente encontrado!\n");
                printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                       componentes[pos].nome,
                       componentes[pos].tipo,
                       componentes[pos].prioridade);
            } else {
                printf("Componente NAO encontrado.\n");
            }

            printf("Comparações da busca: %d\n", comparacoes);
            break;
        }

        default:
            printf("Opção inválida!\n");
        }
    }

    return 0;
}
