	/* Algoritmos y programación I - 95.11 - Curso Ing. Martín Cardozo
	 * Alumno: Joaquín Torres. Padrón 102 822.
	 * Ejercicio 17, guía 1.
	 * Objetivo: Probar la función de biblioteca rand() para diferentes
	 * parámetros, imprimir las cantidades y los porcentajes de cada
	 * número del 0 al 9.
	 */

#include<stdio.h>
#include<stdlib.h>
#define N_SAMPLES 100.0
#define MAX_RAND_VALUE 10
#define SEED 12345

int main(void)
{
	size_t i = 0;
	unsigned int j = 0;
	int random_value;
	size_t count[MAX_VALUE] = {0,0,0,0,0,0,0,0,0,0};
	/*uso cada elemento del arreglo como un contador*/
	
	srand(SEED);
	/*da una seed a rand*/
	for (i = 0; i < N_SAMPLES; i++)
	{
		random_value = rand() % MAX_RAND_VALUE;
		/*printf("%d\n", random_value);*/
		count[random_value] ++;
	}
	
	for (j = 0; j < MAX_RAND_VALUE;j++)
	{
	printf("Cantidad del número %d : %d \n", j, count[j]);
	printf("%s %d  %f %% \n","Porcentaje del número:",j, (count[j]/ TRIES)*100);
	}
	return 0;
}
