#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define TAM 5

#define VAZIO '.'
#define J1 'A'
#define J2 'O'
#define COMP 'X'


void inicializar_tabuleiro(char tabuleiro[TAM][TAM]);

void exibir_tabuleiro(char tabuleiro[TAM][TAM]);

int tabuleiro_cheio(char tabuleiro[TAM][TAM]);

int verificar_vitoria(char tabuleiro[TAM][TAM], char simbolo);

void aplicar_regra_proximidade(char tabuleiro[TAM][TAM], int pulou_vez[3], int lin, int col, char simbolo_atual);

void aplicar_regra_buraco_negro(char tabuleiro[TAM][TAM], int lin, int col);

void jogada_humano(char tabuleiro[TAM][TAM], int pulou_vez[], int jogador, char simbolo);

void jogada_computador(char tabuleiro[TAM][TAM]);


int main()
{
	char tabuleiro[TAM][TAM];
	int pulou_vez[3] = {0, 0, 0};

	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));

	inicializar_tabuleiro(tabuleiro);

	int turno = 1;
	printf(" Trilema do caos \n");
	printf("Alinhe 4 simbolos iguais para vencer e DERROTAR O CAOS!\n");

	while (1) {
		exibir_tabuleiro(tabuleiro);
		
		if (pulou_vez[turno] == 1) {
			printf("\n Jogador %d teve o turno pulado graças a Regra de Proximidade! HAHAHA\n", turno);
			
			pulou_vez[turno] = 0;
		} else {
			if (turno == 1) {
				jogada_humano(tabuleiro, pulou_vez, 1, J1);
				if (verificar_vitoria(tabuleiro, J1) == 1) {
					exibir_tabuleiro(tabuleiro);
					printf("\n PARABÉNS!!! O Jogador 1 venceu o Caos e o Oponente!\n");
					break;
				}
			} else if (turno == 2) {
				jogada_humano(tabuleiro, pulou_vez, 2, J2);
				if (verificar_vitoria(tabuleiro, J2) == 1) {
					exibir_tabuleiro(tabuleiro);
					printf("\n PARABÉNS!!! O Jogador 2 venceu o Caos e o Oponente!\n");
					break;
				}
			} else {
				jogada_computador(tabuleiro);
				if (verificar_vitoria(tabuleiro, COMP) == 1) {
					exibir_tabuleiro(tabuleiro);
					printf("\n O COMPUTADOR VENCEU!! O Caos dominou o tabuleiro. Ambos jogadores perderam! Seus vermes! \n");
					break;
				}
			}
		}

		if (tabuleiro_cheio(tabuleiro) == 1) {
			exibir_tabuleiro(tabuleiro);
			printf("\n EMPATE! O tabuleiro foi completamente tomado pelo caos e ninguem alinhou 4 peças\n");
			break;
		}

		turno = (turno % 3) + 1;
	}

	return 0;
}

void inicializar_tabuleiro(char tabuleiro[TAM][TAM]) {
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			tabuleiro[i][j] = VAZIO;
		}
	}
}

void exibir_tabuleiro(char tabuleiro[TAM][TAM]) {
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

int tabuleiro_cheio(char tabuleiro[TAM][TAM]) {
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			if (tabuleiro[i][j] == VAZIO) return 0;
		}
	}
	return 1;
}

int verificar_vitoria(char tabuleiro[TAM][TAM], char simbolo) {
	
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

void aplicar_regra_proximidade(char tabuleiro[TAM][TAM], int pulou_vez[3], int lin, int col, char simbolo_atual) {
	char adversario = (simbolo_atual == J1) ? J2 : J1;
	int jogador_atual_idx = (simbolo_atual == J1) ? 1 : 2;

	int d_lin[] = {-1, 1, 0, 0};
	int d_col[] = {0, 0, -1, 1};

	for (int i = 0; i < 4; i++) {
		int nova_l = lin + d_lin[i];
		int nova_c = col + d_col[i];

		if (nova_l >= 0 && nova_l < TAM && nova_c >= 0 && nova_c < TAM) {
			if (tabuleiro[nova_l][nova_c] == adversario) {
				printf("\n VOCÊ ATIVOU A REGRA 1! Você jogou ao lado do seu adversario. Perderá a proxima rodada!\n");
				pulou_vez[jogador_atual_idx] = 1;
				break;
			}
		}
	}
}

void aplicar_regra_buraco_negro(char tabuleiro[TAM][TAM], int lin, int col) {
	if ((lin == 2 && col == 2) || (lin == 0 && col == 0) || (lin == 0 && col == 4) || (lin == 4 && col == 0) || (lin == 4 && col == 4)) {
		printf("\n O COMPUTADOR ATIVOU A REGRA 2! O Caos acertou um ponto crítico (%d,%d). O tabuleiro se mexeu!\n", lin, col);

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
						printf("Uma peça em (%d,%d) foi expurgada do tabuleiro!\n", i, j);
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

void jogada_humano(char tabuleiro[TAM][TAM], int pulou_vez[], int jogador, char simbolo) {
	int lin, col;
	while (1) {
		printf("\nJogador %d (%c), digite a Linha e Coluna (0 a 4): ", jogador, simbolo);
		if (scanf("%d %d", &lin, &col) != 2) {
			printf("Entrada invalida! Use numeros.\n");
			while (getchar() != '\n');
			continue;
		}

		if (lin >= 0 && lin < TAM && col >= 0 && col < TAM && tabuleiro[lin][col] == VAZIO) {
			tabuleiro[lin][col] = simbolo;
			aplicar_regra_proximidade(tabuleiro, pulou_vez, lin, col, simbolo);
			break;
		} else {
			printf("Posição invalida ou já ocupada! Jogue de novo.\n");
		}
	}
}

void jogada_computador(char tabuleiro[TAM][TAM]) {
	int lin, col;
	printf("\n Turno do Computador (O CAOS!)");

	do {
		lin = rand() % TAM;
		col = rand() % TAM;
	} while (tabuleiro[lin][col] != VAZIO);

	printf(" O Computador jogou em (%d, %d)\n", lin, col);
	tabuleiro[lin][col] = COMP;

	aplicar_regra_buraco_negro(tabuleiro, lin, col);
}			
