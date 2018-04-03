#include<stdio.h>
int main(void)
{
	int j;
	int entrada;
	puts("Ingrese el número (entero) de entradas a promediar:");
	j = scanf("%i",&entrada);
	/*ampersand señala la direccion de memoria de la variable
	 "entrada",j indica si salió bien */
	if (!j)
	{
		fprintf(stderr, "%s\n", "ERROR: Entrada inválida.");
		return 0;
	}
	if (entrada < )
	{
		/* code */
	}
	printf("Contador: %i\n", entrada);

	return 0;
}