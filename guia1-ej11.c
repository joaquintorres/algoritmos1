#include<stdio.h>
#define ERROR_MSG "ERROR: Número incorrecto."
int main(void)
{
	int n;
	scanf("%d", &n);
	if (n<1)
	{
		fprintf(stderr, "%s\n", ERROR_MSG);
		return 1;
	}
	return 0;
}