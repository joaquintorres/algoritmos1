#include <stdio.h>
#include <string.h>
#define MAX_STR 20

int main(void)
{
	char str_a[MAX_STR];
	char str_b[MAX_STR];
	int cmp_value;
	size_t i;
	size_t ch_val_a;
	size_t ch_val_b;

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
	/*seteo el contador en el último caracter*/
	for (i = 0; str_a[i] == str_b[i]; i++);
	/*paso el último caracter de c u a int*/
	ch_val_a = (int)str_a[i];
	ch_val_b = (int)str_b[i];
	
	printf("%d\n", ch_val_a - ch_val_b);
	/*printf("%d\n", i);*/

	return 0;
}