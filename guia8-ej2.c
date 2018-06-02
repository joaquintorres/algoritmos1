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
status_t left_trim(char * string, char ** str_trimmed)
{
	size_t i;
	size_t diff;
	if (string == NULL || str_trimmed == NULL)
		return ERROR_NULL_POINTER;
	for(i = 0; string[i] == " "; i++);
	diff = i;
	if (((*str_trimmed) = (char *) malloc((strlen(string)-diff) * sizeof(char))) == NULL)
	{
		free(*str_trimmed);
		return ERROR_MEMORY;
	}
	for(i; string[i] != '\0'; i++)
		(*str_trimmed)[i-diff] = string[i];

	return OK;
}
int main(int argc, char *argv[])
{
	status_t st;
	char * string;
	char * new_string;
	if ((st = validate_arguments(argc, argv, &string)) != OK)
		return st;
	printf("%s\n", string);
	if ((st = left_trim(string, &new_string)) != OK)
		return st;
	printf("%s\n", new_string);
	return OK;
}