#include<stdio.h>
#define ERROR_MSG "ERROR: Número incorrecto."
int main(void)
{
	int n;
	/* número a ser invertido*/
	int x = 0;
	/* variable que almacena el resto*/
	scanf("%d", &n);
	if (n<1)
	{
		fprintf(stderr, "%s\n", ERROR_MSG);
		return 1;
	}
	while (n != 0)
	{
		x = x*10 + n%10;
		/*toma el resto n%10 y lo acumula multiplicando por 10
		para poder sumarlo apropiadamente*/
		n = n/10;
		/*el multiplo restante*/
	}
	printf("%d\n", x);	
	return 0;
}