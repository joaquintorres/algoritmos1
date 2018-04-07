#include<stdio.h>
#define ENTRADA 5
 
int main(void)
{
	int i;
	int j;
	
	float numero_parcial;
	float total = 0;
	float promedio;
	/*¿cómo haría para que sirva para números muy grandes?*/
	printf("Ingrese %i números para promediar.\n", ENTRADA);
	for (i = 0; i < ENTRADA; i++)
	{
		j = scanf("%f", &numero_parcial);
		/*ampersand señala la direccion de memoria de la variable
	 	"numero_parcial",j indica si salió bien, pero numero_parcial es donde se 
	 	almacena el input */
		if (!j)
		{
			fprintf(stderr, "%s\n", "ERROR: Entrada inválida. Los números con decimal se escriben con punto en lugar de coma.");
			return 1;
		}

		if (numero_parcial < 0)
		{
			fprintf(stderr, "%s\n", "ERROR: número negativo.");
			return 1;
		}
		total += numero_parcial;
	}
	promedio = total / ENTRADA;
	printf("El promedio es: %f\n", promedio);
	return 0;
}