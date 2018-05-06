#include <stdio.h>
#include <string.h>
#define MAX_STR 100

int main(void)
{
	char str[MAX_STR];
	if (fgets(str, MAX_STR + 2, stdin) == NULL)
		return 1;
	/*if (strcmp(str,"\n") == 0)
		printf("%s\n", "Cadena nula.");*/
	if (str[0] == '\n')
	{
		printf("%s\n", "NULL ARTRINF");
	}
	return 0;
}