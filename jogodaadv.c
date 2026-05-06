#include<stdio.h>
#include<locale.h>
#include <stdlib.h>
#include <time.h>



int main()
{
	setlocale(LC_ALL, "Portuguese");
	srand(time(0));

	int numero_secreto = (rand()%20)+1;
	int chute;
	int i = 0;
	do
	{

		i = 0;
		//	printf("O número secreto é %d \n", numero_secreto);
		printf("Digite o número secreto: ");
		scanf("%d", &chute);

		if (chute>numero_secreto)
			printf("O número que você chutou é maior que o número secreto!\n");
		else if (chute<numero_secreto)
			printf("O número que você chutou é menor que o número secreto!\n");

		int i = i + 1;

	}
	while (chute != numero_secreto);
	if(i < 3) {
		printf("Você é ÓTIMO!");
		printf("")
	}
	else if(i <= 6) {
		printf("Você é BOM!");

	}
	else if(i <=10) {
		printf("Você é FRACO");

	}
	else {
		printf("Você é PÉSSIMO!!!");

	}
	printf("\nParabéns, você acertou!");

	while(i < 6);
}
