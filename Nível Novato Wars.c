#include <stdio.h>
#include <string.h>
#include <stdlib.h> // necessário para system()

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    struct Territorio territorios[5];
    int i;

    printf("=== Cadastro de Territorios ===\n");

    for (i = 0; i < 5; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);

        // Lê o nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        // Lê a cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Lê o número de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        while (getchar() != '\n'); // limpa o ENTER do buffer
    }

    // Exibe os territórios cadastrados
    printf("\n=== Dados dos Territorios ===\n");
    for (i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Numero de tropas: %d\n", territorios[i].tropas);
    }

    // Pausa final para que o terminal não feche
    system("pause"); // funciona no Windows

    return 0;
}
