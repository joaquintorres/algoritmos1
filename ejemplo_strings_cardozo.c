#include <stdio.h>
#include <ctype.h>
#define MAX_LINE 100

int main(void)
{
  char line[MAX_LINE + 2];
  int i;
  while ( (fgets(line,MAX_LINE + 2, stdin) ) != NULL)
  {	
  	if(line[0] == '\n')
  		break;
    for (i = 0; line[i] != '\0' && line[i] != '\n'; ++i)
    {
      line[i] = toupper(line[i]);
    }
    puts(line);
  }
  return 0;
}
