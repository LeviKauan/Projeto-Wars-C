#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5  // quantidade fixa de territórios

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* t) {
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);

        printf("Nome do territorio: ");
        fgets(t[i].nome, sizeof(t[i].nome), stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(t[i].cor, sizeof(t[i].cor), stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &t[i].tropas);
        while(getchar() != '\n');
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio* t) {
    printf("\n=== Estado Atual dos Territorios ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n%s (cor %s) ataca %s (cor %s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        defensor->tropas -= 1;
        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            strcpy(defensor->cor, atacante->cor);
            printf("\nVITÓRIA DO ATACANTE!\n");
            printf("%s venceu a batalha contra %s, conquistando aos poucos o territorio inimigo!\n",
                   atacante->nome, defensor->nome);
            printf("O Territorio %s foi conquistado pelo Exército %s!\n", defensor->nome, defensor->cor);
        } else {
            printf("\nVITÓRIA DO ATACANTE!\n");
            printf("%s venceu a batalha contra %s, conquistando aos poucos o territorio inimigo!\n",
                   atacante->nome, defensor->nome);
        }
    } else {
        // Defensor vence
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("\nVITÓRIA DO DEFENSOR!\n");
        printf("%s defendeu seu territorio com êxito na batalha contra %s\n",
               defensor->nome, atacante->nome);

        // Nova regra: se atacante ficar com 0 tropas, defensor conquista atacante
        if (atacante->tropas == 0) {
            strcpy(atacante->cor, defensor->cor);
            atacante->tropas = 1; // mantém ao menos 1 tropa após conquista
            printf("O Territorio %s foi conquistado pelo Exército %s após destruir o atacante!\n",
                   atacante->nome, atacante->cor);
        }
    }

    // Garantir que tropas nunca fiquem negativas
    if (defensor->tropas < 0) defensor->tropas = 0;
}

// Função para liberar memória alocada
void liberarMemoria(Territorio* t) {
    free(t);
}

int main() {
    srand(time(NULL));

    Territorio* territorios = (Territorio*) calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (!territorios) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    cadastrarTerritorios(territorios);

    int opcao = 1;
    while(opcao != 0) {
        exibirTerritorios(territorios);

        printf("\nDeseja realizar um ataque? (1 = sim, 0 = nao): ");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        if (opcao == 1) {
            int atac, def;
            printf("Escolha o territorio atacante (numero 1 a 5): ");
            scanf("%d", &atac);
            while(getchar() != '\n');

            printf("Escolha o territorio defensor (numero 1 a 5): ");
            scanf("%d", &def);
            while(getchar() != '\n');

            atacar(&territorios[atac-1], &territorios[def-1]);
        }
    }

    exibirTerritorios(territorios);
    liberarMemoria(territorios);

    system("pause");
    return 0;
}