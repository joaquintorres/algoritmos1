#include <stdio.h>
#include <string.h>
#define MAX_STR 13
int main (void)
{
	char initial_str[MAX_STR];
	char copied_str[MAX_STR];
	size_t i;
	if (fgets(initial_str, MAX_STR, stdin) == NULL)
	{
		fprintf(stderr, "%s\n", "FUCK");
		return 1;
	}
	for (i=0;(copied_str[i] = initial_str[i]); i++);

	printf("%s\n", copied_str);
	return 0;
}