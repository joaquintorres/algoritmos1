#include <stdio.h>
#include <stdlib.h>

int compare_double(const void * a,const void * b)
{
	double diff;
	diff = (*(double *)a - *(double *)b);
	if (diff > 0)
		return 1;
	if (diff < 0)
		return (-1);
	return 0;
}
int main(void)
{
	size_t i;
	double key = 999.999;
	double values[] = {1111112,2.555,34,3.11134,1000,999.999,0.0,55.5};
	for (i = 0; i < 8; i++)
	{
		printf("%f ", values[i]);
	}
	fputc('\n', stdout);
	qsort(values,8,sizeof(double),compare_double);
	for (i = 0; i < 8; i++)
	{
		printf("%f ", values[i]);
	}
	fputc('\n', stdout);
	if ((bsearch((void *)&key,values,8,sizeof(double),compare_double)) == NULL)
		printf("%s\n", "Match not found!");
	else
		printf("%s\n", "Match found!");
	return 0;
}