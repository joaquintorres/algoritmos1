#include <stdio.h>
#define TOTAL_CREDITS 240
#define YEAR_MSG "Ud. se encuentra en el"

int main(void){
	int credits;
	int yearly_credits;
	int j;
	printf("Ingrese su número de créditos \n");
	j = scanf("%d", &credits);
	if(!j){
		fprintf(stderr, "ERROR: Entrada inválida.\n");
		return 1;
	}
	if(credits < 0){
		fprintf(stderr, "ERROR:Número negativo.\n");
		return 1;
	}
	
	/*Uso la division entera porque no hay medios créditos o cosas
	así */
	
	yearly_credits = TOTAL_CREDITS / 5;
	
	if(credits > TOTAL_CREDITS)
	{
		printf("Ud. ya se encuentra en condiciones de recibirse. Vuelva a su tésis.\n");
		return 0;
	}
	
	if (credits < yearly_credits)
	{
		printf("%s %s", YEAR_MSG, "primer año.\n");
	}else
	{
		if(credits < yearly_credits * 2)
		{
			printf("%s %s", YEAR_MSG, "segundo año.\n");
		}else{
			if(credits < yearly_credits * 3)
			{
				printf("%s %s", YEAR_MSG, "tercer año.\n");
			}else
			{
				printf("%s %s", YEAR_MSG, "cuarto año.\n");
			}		
		}
	}
	
	return 0;
}
