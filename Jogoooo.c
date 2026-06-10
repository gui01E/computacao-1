#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5

#define VAZIO '.'
#define J1 'A'  
#define J2 'O'  
#define COMP 'X' 

char tabuleiro[TAM][TAM];
int pulou_vez[3] = {0, 0, 0}; 

void inicializar_tabuleiro() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = VAZIO;
        }
    }
}

void exibir_tabuleiro() {
    printf("\n    0   1   2   3   4\n");
    printf("  ---------------------\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d |", i);
        for (int j = 0; j < TAM; j++) {
            printf(" %c |", tabuleiro[i][j]);
        }
        printf("\n  ---------------------\n");
    }
}

int tabuleiro_cheio() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == VAZIO) return 0;
        }
    }
    return 1;
}

int verificar_vitoria(char simbolo) {
    // Horizontal e Vertical
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j <= TAM - 4; j++) {
            if (tabuleiro[i][j] == simbolo && tabuleiro[i][j+1] == simbolo && 
                tabuleiro[i][j+2] == simbolo && tabuleiro[i][j+3] == simbolo) return 1;
            if (tabuleiro[j][i] == simbolo && tabuleiro[j+1][i] == simbolo && 
                tabuleiro[j+2][i] == simbolo && tabuleiro[j+3][i] == simbolo) return 1;
        }
    }
    for (int i = 0; i <= TAM - 4; i++) {
        for (int j = 0; j <= TAM - 4; j++) {
            // Diagonal Principal (\)
            if (tabuleiro[i][j] == simbolo && tabuleiro[i+1][j+1] == simbolo && 
                tabuleiro[i+2][j+2] == simbolo && tabuleiro[i+3][j+3] == simbolo) return 1;
            // Diagonal Secundária (/)
            if (tabuleiro[i][j+3] == simbolo && tabuleiro[i+1][j+2] == simbolo && 
                tabuleiro[i+2][j+1] == simbolo && tabuleiro[i+3][j] == simbolo) return 1;
        }
    }
    return 0;
}

void aplicar_regra_proximidade(int lin, int col, char simbolo_atual) {
    char adversario = (simbolo_atual == J1) ? J2 : J1;
    int jogador_atual_idx = (simbolo_atual == J1) ? 1 : 2;

    int d_lin[] = {-1, 1, 0, 0};
    int d_col[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nova_l = lin + d_lin[i];
        int nova_c = col + d_col[i];

        if (nova_l >= 0 && nova_l < TAM && nova_c >= 0 && nova_c < TAM) {
            if (tabuleiro[nova_l][nova_c] == adversario) {
                printf("\n REGRA 1 ATIVADA! Você jogou ao lado do seu adversario. Perderá a proxima rodada!\n");
                pulou_vez[jogador_atual_idx] = 1; 
                break;
            }
        }
    }
}

void aplicar_regra_buraco_negro(int lin, int col) {
    // Ativa apenas no centro (2,2) ou nos 4 cantos
    if ((lin == 2 && col == 2) || (lin == 0 && col == 0) || (lin == 0 && col == 4) || (lin == 4 && col == 0) || (lin == 4 && col == 4)) {
        printf("\n REGRA 2 ATIVADA! O Caos caiu em um ponto gravitacional (%d,%d). O tabuleiro se moveu!\n", lin, col);
        
        char novo_tabuleiro[TAM][TAM];
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                novo_tabuleiro[i][j] = VAZIO;
            }
        }

        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (tabuleiro[i][j] != VAZIO && (i != lin || j != col)) {
                    int nova_l = i;
                    int nova_c = j;

                    if (i < lin) nova_l--;
                    else if (i > lin) nova_l++;

                    if (j < col) nova_c--;
                    else if (j > col) nova_c++;

                    if (nova_l >= 0 && nova_l < TAM && nova_c >= 0 && nova_c < TAM) {
                        novo_tabuleiro[nova_l][nova_c] = tabuleiro[i][j];
                    } else {
                        printf("Uma peça em (%d,%d) foi ejetada do tabuleiro!\n", i, j);
                    }
                }
            }
        }
        
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                tabuleiro[i][j] = novo_tabuleiro[i][j];
            }
        }
        tabuleiro[lin][col] = COMP;
    }
}

void jogada_humano(int jogador, char simbolo) {
    int lin, col;
    while (1) {
        printf("\nJogador %d (%c), digite a Linha e Coluna (0 a 4): ", jogador, simbolo);
        if (scanf("%d %d", &lin, &col) != 2) {
            printf("Entrada invalida! Use numeros.\n");
            while (getchar() != '\n'); // Limpa o buffer do teclado
            continue;
        }

        if (lin >= 0 && lin < TAM && col >= 0 && col < TAM && tabuleiro[lin][col] == VAZIO) {
            tabuleiro[lin][col] = simbolo;
            aplicar_regra_proximidade(lin, col, simbolo);
            break;
        } else {
            printf("Posicao invalida ou ja ocupada! Tente novamente.\n");
        }
    }
}

void jogada_computador() {
    int lin, col;
    printf("\n "Turno do Computador (O Caos)...");
    
    do {
        lin = rand() % TAM;
        col = rand() % TAM;
    } while (tabuleiro[lin][col] != VAZIO);

    printf(" O Computador jogou em (%d, %d)\n", lin, col);
    tabuleiro[lin][col] = COMP;

    aplicar_regra_buraco_negro(lin, col);
}

int main() {
    srand(time(NULL));
    inicializar_tabuleiro();
    
    int turno = 1; // 1 = J1, 2 = J2, 3 = Computador
    printf("=== BEM-VINDO AO TRILEMA DO CAOS ===\n");
    printf("Alinhe 4 simbolos iguais para vencer.\n");
    printf("Avisos: Evite colar no seu oponente humano, e cuidado com o centro e cantos!\n");

    while (1) {
        exibir_tabuleiro();
        if (pulou_vez[turno] == 1) {
            printf("\n Jogador %d teve o turno pulado devido a Regra de Proximidade!\n", turno);
            pulou_vez[turno] = 0; // Reseta a punição (Falso)
        } else {
            if (turno == 1) {
                jogada_humano(1, J1);
                if (verificar_vitoria(J1) == 1) {
                    exibir_tabuleiro();
                    printf("\n PARABÉNS! O Jogador 1 (A) venceu o Caos e o Oponente!\n");
                    break;
                }
            } else if (turno == 2) {
                jogada_humano(2, J2);
                if (verificar_vitoria(J2) == 1) {
                    exibir_tabuleiro();
                    printf("\n PARABÉNS! O Jogador 2 (O) venceu o Caos e o Oponente!\n");
                    break;
                }
            } else {
                jogada_computador();
                if (verificar_vitoria(COMP) == 1) {
                    exibir_tabuleiro();
                    printf("\n O COMPUTADOR VENCEU! O Caos dominou o tabuleiro. Ambos jogadores perderam!\n");
                    break;
                }
            }
        }

        if (tabuleiro_cheio() == 1) {
            exibir_tabuleiro();
            printf("\n EMPATE! O tabuleiro foi completamente tomado pelo caos e ninguem alinhou 4 peças.\n");
            break;
        }

        turno = (turno % 3) + 1;
    }

    return 0;
}
