#include <stdio.h>
#include <string.h>
#define MAX_STR 1000

int main(void)
{
	char str[MAX_STR];
	int i;
	int len;
	if (fgets(str, MAX_STR, stdin) == NULL)
	{
		fprintf(stderr, "%s\n", "Fuck up");
		return 1;
	}
	len = strlen (str);
	
	for (i = len - 1; i >= 0; i--)
		printf("%c", str[i]);
	printf("\n");
	return 0;
}