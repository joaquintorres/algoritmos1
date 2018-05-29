#include <stdio.h>

#define CUTOFF_DIFFERENCE 0.000000000000000000000000000000000000000000001

long double factorial(size_t n)
{
	if (n <= 1)
		return 1;
	return n*factorial(n-1);
}
int main(void)
{
	size_t n;
	double diff;
	double guess;
	FILE * results_ptr;
	if((results_ptr = fopen("results_e.dat", "wt")) == NULL)
		return 1;
	for (n = 1, diff = 1, guess = 1; diff > CUTOFF_DIFFERENCE; n++)
	{
		diff = 1/factorial(n) - 1/factorial(n+1);
		guess += 1/factorial(n);
		printf("%f %.100f \n", guess, diff);
		fprintf(results_ptr, "%.100f\n", guess);
	}
	fclose(results_ptr);
	return 0;
}
