#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 3
#define MIN_ARGS 3

#define CMD_ARG_STR_TOKEN_POSITION 1
#define CMD_ARG_STR_TOKEN_VALUE 2
#define CMD_ARG_STR_FLAG "-s"
typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_INVALID_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG
} status_t;

status_t validate_arguments(int argc, char *argv[], char ** string)
{
	if (argv == NULL || string == NULL)
		return ERROR_NULL_POINTER;
	if (argc > MAX_ARGS || argc < MIN_ARGS)
		return ERROR_INVALID_NUMBER_OF_ARGUMENTS;
	if (strcmp(argv[CMD_ARG_STR_TOKEN_POSITION], CMD_ARG_STR_FLAG))
		return ERROR_INVALID_FLAG;
	*string = argv[CMD_ARG_STR_TOKEN_VALUE];
	return OK;
}

status_t clone_string(const char * string, char ** copy)
{
	if (string == NULL || copy == NULL)
		return ERROR_NULL_POINTER;
	if((*copy = (char *) malloc((strlen(string) + 2) * sizeof (char))) == NULL)
	{
			free(*copy);
			*copy = NULL;
			return ERROR_MEMORY;
	}
	if (strcpy(*copy, string) == NULL)
		return ERROR_NULL_POINTER;
	return OK;
}

int main(int argc, char * argv[])
{
	char * string;
	char * copy;
	status_t st;
	if ((st = validate_arguments(argc, argv, &string)) != OK)
		return st;
	printf("%s\n", string);
	if ((st = clone_string(string,&copy)) != OK)
		return st;
	printf("%s\n", copy);
	return OK;
}

