#include <stdio.h>
#include <string.h>

// Criação da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    struct Territorio territorios[5]; // vetor para armazenar 5 territórios
    int i;

    printf("=== Cadastro de Territorios ===\n");

    // Entrada de dados
    for(i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i+1);

        printf("Nome do territorio: ");
        scanf(" %[^\n]s", territorios[i].nome); // lê com espaços

        printf("Cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados
    printf("\n=== Dados dos Territorios Cadastrados ===\n");
    for(i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i+1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}