#include <stdio.h>
#include <string.h>
#define MAX_STR 20

int main(void)
{
	char str_a[MAX_STR];
	char str_b[MAX_STR];
	int cmp_value;
	int i;
	if (fgets(str_a,MAX_STR,stdin) == NULL)
	 {
	 	fprintf(stderr, "%s\n", "FUCK");
	 	return 1;
	 } 
	if (fgets(str_b,MAX_STR,stdin) == NULL)
	 {
	 	fprintf(stderr, "%s\n", "FUCK");
	 	return 1;
	 } 
	cmp_value = strcmp(str_a, str_b);
	printf("%d\n", cmp_value);

	for (int i = 0; str_a[i] != '\n' && str_b[i] != '\n'; ++i)
	{
		if (str_a[i] == str_b[i])
			continue;
		
	}
	if (str_a[i] == str_b[i])
		{
			printf("%d\n", 0);
		}
	return 0;
}