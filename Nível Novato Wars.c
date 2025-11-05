#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Cada território possui um nome, cor do exército e quantidade de tropas
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Declaração de um vetor de 5 territórios
    Territorio territorios[5];

    printf("=== Cadastro de Territorios ===\n");

    // Laço para cadastrar os 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", territorios[i].nome); // Lê até a quebra de linha

        // Entrada da cor do exército
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor); // Lê string sem espaços

        // Entrada da quantidade de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n=== Dados dos Territorios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Numero de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}