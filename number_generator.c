#include <stdio.h>
#define MAX_NMBR 1000000000

void print_values(void);

int main(void)
{
	print_values();
	return 0;
}

void print_values(void)
{
	size_t i;
	for (i = 0; i < MAX_NMBR; ++i)
		printf("%d\n", i);
}