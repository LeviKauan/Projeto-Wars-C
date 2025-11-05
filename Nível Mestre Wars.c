#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5
#define MAX_MISSAO 100

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
    int vitoriasAtaque;
    int vitoriasDefesa;
    int territoriosConquistados;
} Territorio;

// Funcao que sorteia uma missao pro jogador
void atribuirMissao(char** missaoJogador, Territorio* jogador, Territorio* mapa, int tamanho, int* tipoMissao, int* objetivo) {
    char buf[MAX_MISSAO];

    // missao 1 = conquistar um territorio aleatorio
    int alvo = rand() % tamanho;
    snprintf(buf, MAX_MISSAO, "Conquistar o territorio %s", mapa[alvo].nome);

    // missao 2 = conquistar ate 2 territorios
    int x = rand() % 2 + 1;

    // missao 3 = realizar 1 a 5 ataques ou defesas com exito
    int y = rand() % 5 + 1;

    int indice = rand() % 3;
    *missaoJogador = (char*) malloc(MAX_MISSAO);
    switch(indice) {
        case 0: strcpy(*missaoJogador, buf); *tipoMissao = 0; *objetivo = alvo; break;
        case 1: snprintf(*missaoJogador, MAX_MISSAO, "Conquistar %d territorios inimigos", x); *tipoMissao = 1; *objetivo = x; break;
        case 2: snprintf(*missaoJogador, MAX_MISSAO, "Realizar %d ataques ou defesas com exito", y); *tipoMissao = 2; *objetivo = y; break;
    }

    // mostrar a missao
    printf("\nExercito %s do Territorio %s, sua missao e: %s\n",
           jogador->cor, jogador->nome, *missaoJogador);
}

// Funcao que gera o mapa com nomes e cores aleatorias
void gerarMapa(Territorio* t) {
    char* nomes[] = {
        "Coreia", "Japao", "Estados Unidos", "Brasil", "Jamaica",
        "Canada", "Roma", "Grecia", "Russia", "Portugal",
        "Italia", "Alemanha", "Holanda", "Ucrania"
    };
    char* cores[] = {
        "Rosa", "Azul", "Amarelo", "Preto", "Branco",
        "Vermelho", "Ciano", "Cinza", "Verde", "Roxo",
        "Laranja", "Bege"
    };

    int indicesUsados[NUM_TERRITORIOS];
    for (int i = 0; i < NUM_TERRITORIOS; i++) indicesUsados[i] = -1;

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        int idx;
        do { idx = rand() % (sizeof(nomes)/sizeof(nomes[0])); } 
        while(idx == indicesUsados[0] || idx == indicesUsados[1] || idx == indicesUsados[2] || idx == indicesUsados[3] || idx == indicesUsados[4]);
        indicesUsados[i] = idx;
        strcpy(t[i].nome, nomes[idx]);

        int cidx = rand() % (sizeof(cores)/sizeof(cores[0]));
        strcpy(t[i].cor, cores[cidx]);

        t[i].tropas = rand() % 6 + 5; // 5 a 10 tropas
        t[i].vitoriasAtaque = 0;
        t[i].vitoriasDefesa = 0;
        t[i].territoriosConquistados = 0;
    }
}

// mostrar mapa do mundo
void exibirTerritorios(Territorio* t) {
    printf("\n=== Mapa do Mundo ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

// funcao que realiza ataques entre territorios
void atacar(Territorio* atacante, Territorio* defensor, Territorio* jogador, int* missaoConcluida, int tipoMissao, int objetivo) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n%s (cor %s) ataca %s (cor %s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    int atacanteVence = dadoAtacante > dadoDefensor;

    if (atacanteVence) {
        defensor->tropas -= 1;
        if (atacante == jogador) jogador->vitoriasAtaque++;
        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            strcpy(defensor->cor, atacante->cor);
            if (atacante == jogador) jogador->territoriosConquistados++;

            printf("\nVITORIA DO ATACANTE!\n");
            printf("%s venceu a batalha contra %s, conquistando aos poucos o territorio inimigo!\n",
                   atacante->nome, defensor->nome);
            printf("O Territorio %s foi conquistado pelo Exercito %s!\n", defensor->nome, defensor->cor);
        } else if (atacante == jogador) {
            printf("\nVITORIA DO ATACANTE!\n");
            printf("%s venceu a batalha contra %s, conquistando aos poucos o territorio inimigo!\n",
                   atacante->nome, defensor->nome);
        }
    } else {
        atacante->tropas -= 1;
        if (defensor == jogador) jogador->vitoriasDefesa++;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("\nVITORIA DO DEFENSOR!\n");
        printf("%s defendeu seu territorio com exito na batalha contra %s\n",
               defensor->nome, atacante->nome);

        if (atacante->tropas == 0 && defensor == jogador) {
            strcpy(atacante->cor, defensor->cor);
            atacante->tropas = 1;
            jogador->territoriosConquistados++;
            printf("O Territorio %s foi conquistado pelo Exercito %s apos destruir o atacante!\n",
                   atacante->nome, atacante->cor);
        }
    }

    // verificar se missao foi concluida
    if (tipoMissao == 0 && jogador->territoriosConquistados >= 1) *missaoConcluida = 1;
    if (tipoMissao == 1 && jogador->territoriosConquistados >= objetivo) *missaoConcluida = 1;
    if (tipoMissao == 2 && (jogador->vitoriasAtaque + jogador->vitoriasDefesa) >= objetivo) *missaoConcluida = 1;

    if (defensor->tropas < 0) defensor->tropas = 0;
}

// libera memoria alocada
void liberarMemoria(Territorio* t, char* missao) {
    free(t);
    free(missao);
}

int main() {
    srand(time(NULL));

    Territorio* territorios = (Territorio*) calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (!territorios) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    gerarMapa(territorios);

    char* missao = NULL;
    int tipoMissao, objetivo, missaoConcluida = 0;
    atribuirMissao(&missao, &territorios[0], territorios, NUM_TERRITORIOS, &tipoMissao, &objetivo);

    exibirTerritorios(territorios); // mapa mostrado apos a missao

    int opcao = 1;
    while(opcao != 0 && !missaoConcluida) {
        printf("\nDeseja realizar um ataque? (1 = sim, 0 = nao): ");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        if (opcao == 1) {
            int atac, def;
            printf("Escolha o territorio atacante (1 a 5): ");
            scanf("%d", &atac);
            while(getchar() != '\n');
            printf("Escolha o territorio defensor (1 a 5): ");
            scanf("%d", &def);
            while(getchar() != '\n');

            atacar(&territorios[atac-1], &territorios[def-1], &territorios[0], &missaoConcluida, tipoMissao, objetivo);
        }
    }

    // Mensagem final
    if (missaoConcluida) {
        printf("\nVoce executou sua missao com exito! Obrigado por jogar!\n");
    } else {
        printf("\nFim de jogo! Missao nao concluida.\n");
    }

    liberarMemoria(territorios, missao);
    system("pause");
    return 0;
}