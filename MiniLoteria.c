#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int sorteados[3], chute[3];
    int tentativas, acertos, total_tentativas_geral = 0;
    char repetir;

    srand(time(NULL));

    do {
        // Sorteia 3 números diferentes entre 1 e 20
        for (int i = 0; i < 3; i++) {
            int novo_num;
            int repetido;
            do {
                repetido = 0;
                novo_num = (rand() % 20) + 1;
                for (int j = 0; j < i; j++) {
                    if (sorteados[j] == novo_num) repetido = 1;
                }
            } while (repetido);
            sorteados[i] = novo_num;
        }

        // APENAS PARA TESTE: Mostra os números sorteados
        printf("\n--- [DEBUG] Números sorteados: %d, %d, %d ---\n", sorteados[0], sorteados[1], sorteados[2]);

        tentativas = 0;
        acertos = 0;

        while (acertos < 3) {
            tentativas++;
            acertos = 0;
            printf("\nTentativa %d. Digite 3 números (1-20): ", tentativas);
            scanf("%d %d %d", &chute[0], &chute[1], &chute[2]);

            // Verifica quantos números o usuário acertou
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (chute[i] == sorteados[j]) {
                        acertos++;
                        break; 
                    }
                }
            }

            if (acertos < 3) printf("Você acertou %d número(s). Tente novamente!\n", acertos);
        }

        total_tentativas_geral += tentativas;

        // Classificação
        printf("\nPARABÉNS! Você acertou os 3 números em %d tentativas.\n", tentativas);
        printf("Gasto nesta rodada: R$ %d,00\n", tentativas);
        printf("Classificação: ");

        if (tentativas <= 30) printf("ÓTIMO\n");
        else if (tentativas <= 60) printf("BOM\n");
        else if (tentativas <= 100) printf("FRACO\n");
        else printf("PÉSSIMO\n");

        // Condição para repetir rodada
        repetir = 'n';
        if (tentativas > 60) {
            printf("\nDeseja tentar uma nova rodada? (s/n): ");
            scanf(" %c", &repetir);
        }

    } while (repetir == 's' || repetir == 'S');

    printf("\n========================================");
    printf("\nTotal gasto em todas as rodadas: R$ %d,00\n", total_tentativas_geral);
    printf("========================================\n");

    return 0;
}
