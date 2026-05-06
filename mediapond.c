#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>

int main() {

	setlocale(LC_ALL, "Portuguese");
	int i;
	int n;
	float a, b, c, resultado;
	printf("Digite o Número de casos:");
	scanf("%d", &n);

	for( i = 1; i <= n; i = i + 1 ) {

		printf("\nCaso %d:\n", i);
		printf("Digite três números:");
		scanf("%f %f %f", &a, &b, &c);
		resultado = ((a*2 + b*3 + c*5) / 10);
		printf("O valor da média ponderada é: %f\n", resultado);


	}

	return 0;
}
