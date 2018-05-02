#include <stdio.h>
#include <string.h>
#define MAX_STR 100
#define UPPER_ASCII_BOUND 123
#define LOWER_ASCII_BOUND 96
#define ASCII_STEP 32

int main(void)
{
	char usr_str[MAX_STR];
	size_t i;
	size_t ch;

	if (fgets(usr_str,MAX_STR + 2,stdin) == NULL)
	 {
	 	fprintf(stderr, "%s\n", "FUCK");
	 	return 1;
	 } 
	for (i = 0;usr_str[i] != '\n' && usr_str[i] != '\n'; ++i)
	{
		ch = (int)usr_str[i];
		if ((ch > LOWER_ASCII_BOUND) && (ch < UPPER_ASCII_BOUND))
			ch -= ASCII_STEP;
		usr_str[i] = (char)ch;
	}
	printf("%s\n", usr_str);
	return 0;
}