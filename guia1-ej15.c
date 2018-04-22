 	/* Algoritmos y programación I - 95.11 - Curso Ing. Martín Cardozo
	 * Alumno: Joaquín Torres. Padrón 102 822.
	 * Ejercicio 15, guía 1.
	 * Objetivo: Promediar una cantidad arbitraria de números ingresados por
	 * el usuario.
	 */

#include<stdio.h>
#define MAX_NUMBERS 5
 
int main(void)
{
	size_t i;
	
	
	float sum;
	float total = 0;
	float average;
	
	printf("Ingrese %d números para promediar.\n", AMOUNT_NUMBERS);
	for (i = 0, sum=0; i < MAX_NUMBERS; i++)
	{
		int j = scanf("%f", sum);
		/*ampersand señala la direccion de memoria de la variable
	 	"sum",j indica si salió bien, pero sum es donde se 
	 	almacena el input */
		if (!j)
		{
			fprintf(stderr, "%s\n", "ERROR: Entrada inválida.");
			return 1;
		}

		if (j == EOF)
		{
			fprintf(stderr, "%s\n", "ERROR: Entrada inválida.");
			return 1;
		}

		if (sum < 0)
		{
			fprintf(stderr, "%s\n", "ERROR: Número negativo.");
			return 1;
		}
		total += sum;
	}
	average = total / AMOUNT_NUMBERS;
	printf("%s %f \n","El promedio es:", average);
	return 0;
}
