/*Cálculo de polinomios en un punto por método de Horner.*/
#include <stdio.h>
#define MAX_ARRAY 3

/*PROTOTIPO*/
int horner_calculate(size_t degree, float * coefficients, float point, float * result);

int main(void)
{
	float coefficients[MAX_ARRAY] = {1,2,3};
	float result;

	if ((horner_calculate(MAX_ARRAY - 1, coefficients, 2, &result)) != 0)
		return 1;
	printf("%.20f\n", result);
	return 0;
}

int horner_calculate(size_t degree, float * coefficients, float point, float * result)
{
	float aux;
	int i;

	if (coefficients == NULL || result == NULL)
		return 1;

	
	for (i = degree, aux = 0; i >= 0; --i)
	{		
		printf("%f\n", aux);
		aux = coefficients[i] + point * aux;
	}
	*result = aux;
	return 0;
}