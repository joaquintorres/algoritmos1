#include <stdio.h>
#define MAX_STR 20

int main (void)
{
	char temp[MAX_STR];
	/*scanf("%s", temp);*/
	if (fgets(temp,MAX_STR + 2,stdin)== NULL)
		return 1;
	printf("%s\n", temp);
	return 0;
}