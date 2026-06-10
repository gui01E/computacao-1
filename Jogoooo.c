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
            if (tabuleiro[i][j] == simbolo && tabuleiro[i+1][j+1] == simbolo && 
                tabuleiro[i+2][j+2] == simbolo && tabuleiro[i+3][j+3] == simbolo) return 1;
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
    if ((lin == 2 && col == 2) || (lin == 0 && col == 0) || (lin == 0 && col == 4) || (lin == 4 && col == 0) || (lin == 4 && col == 4)) {
        printf("\n REGRA 2 ATIVADA! O Caos caiu em um ponto gravitacional (%d,%d). O tabuleiro se mexeu!\n", lin, col);
        
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
    return 0;
}
