#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define N 10

int main() {
	int vetor[N];
	int i, posicao;

	srand(time(NULL));

	printf("Vetores:\n");
	for (i = 0; i < N; i++) {
		vetor[i] = rand() % 30;
		printf("%d ", vetor[i]);
	}

	printf("\n\nDigite a posição que deverá ser removida (0 a %d): ", N - 1);
	scanf("%d", &posicao);

	if (posicao < 0 || posicao >= N) {
		printf("Seu inútil, está errado!\n");
		return 1;
	}

	for (i = posicao; i < N - 1; i++) {
		vetor[i] = vetor[i + 1];
	}

	vetor[N - 1] = 0;

	printf("\nNovo vetor:\n");
	for (i = 0; i < N; i++) {
		printf("%d ", vetor[i]);
	}

	printf("\n");

	return 0;
}
