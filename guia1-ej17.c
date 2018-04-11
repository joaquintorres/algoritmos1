#include<stdio.h>
#include<stdlib.h>
#define TRIES 1000000000000.0
#define VALOR_MAX 10

int main(void)
{
	unsigned int i = 0;
	/* contador*/
	unsigned int valor_azar;

	float cuenta_cero = 0;
	float cuenta_uno = 0;
	float cuenta_dos = 0;
	float cuenta_tres = 0;
	float cuenta_cuatro = 0;
	float cuenta_cinco = 0;
	float cuenta_seis = 0;
	float cuenta_siete = 0;
	float cuenta_ocho = 0;
	float cuenta_nueve = 0;

	for (i = 0; i < TRIES; ++i)
	{
		valor_azar = rand() % VALOR_MAX;
		/* printf("%d\n", valor_azar); */
		if (valor_azar == 0)
		{
			cuenta_cero++;
			continue;
		}if (valor_azar == 1)
		{
			cuenta_uno++;
			continue;
		}if (valor_azar == 2)
		{
			cuenta_dos++;
			continue;
		}if (valor_azar == 3)
		{
			cuenta_tres++;
			continue;
		}if (valor_azar == 4)
		{
			cuenta_cuatro++;
			continue;
		}if (valor_azar == 5)
		{
			cuenta_cinco++;
			continue;
		}if (valor_azar == 6)
		{
			cuenta_seis++;
			continue;
		}if (valor_azar == 7)
		{
			cuenta_siete++;
			continue;
		}if (valor_azar == 8)
		{
			cuenta_ocho++;
			continue;
		}if (valor_azar == 9)
		{
			cuenta_nueve++;
			continue;
		}
		/*cómo hago esto más eficientemente?*/

	}
	printf("Porcentaje de ceros: %f \n", (cuenta_cero / TRIES)*100);
	printf("Porcentaje de unos: %f \n", (cuenta_uno / TRIES)*100);
	printf("Porcentaje de dos : %f \n", (cuenta_dos / TRIES)*100);
	printf("Porcentaje de tres: %f \n", (cuenta_tres / TRIES)*100);
	printf("Porcentaje de cuatros : %f \n", (cuenta_cuatro / TRIES)*100);
	printf("Porcentaje de cincos: %f \n", (cuenta_cinco / TRIES)*100);
	printf("Porcentaje de seis: %f \n", (cuenta_seis / TRIES)*100);
	printf("Porcentaje de sietes: %f \n", (cuenta_siete / TRIES)*100);
	printf("Porcentaje de ochos: %f \n", (cuenta_ocho / TRIES)*100);
	printf("Porcentaje de nueves : %f \n", (cuenta_nueve / TRIES)*100);

	return 0;
}