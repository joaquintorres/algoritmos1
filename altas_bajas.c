#include <stdio.h>

#define MIN_ARGUMENTS 5
#define MAX_ARGUMENTS 5

#define CMD_ARG_INVENTORY_FILE_TOKEN_POSITION 1
#define CMD_ARG_INVENTORY_FILE_TOKEN_VALUE 2
#define CMD_ARG_INVENTORY_FILE_FLAG "-i"

#define CMD_ARG_APPENDED_FILE_TOKEN_POSITION 3
#define CMD_ARG_APPENDED_FILE_TOKEN_VALUE 4
#define CMD_ARG_APPENDED_FILE_FLAG "-a"

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_BAD_INPUT,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_FILE,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_NUMBER
} status_t;

status_t validate_arguments(int argc, char * argv[], char ** inventory_file_path, char ** appended_file_path)
{
	if (appended_file_path == NULL || inventory_file_path == NULL)
		return ERROR_NULL_POINTER;
	if(argc > MAX_ARGUMENTS || argc < MIN_ARGUMENTS)
		return ERROR_NUMBER_OF_ARGUMENTS;
	
	if (strcmp(argv[CMD_ARG_INVENTORY_FILE_TOKEN_POSITION], CMD_ARG_INVENTORY_FILE_FLAG))
		return ERROR_INVALID_FLAG; 
	*inventory_file_path = argv[CMD_ARG_INVENTORY_FILE_TOKEN_VALUE];
	
	if (strcmp(argv[CMD_ARG_APPENDED_FILE_TOKEN_POSITION], CMD_ARG_APPENDED_FILE_FLAG))
		return ERROR_INVALID_FLAG;

	*appended_file_path = argv[CMD_ARG_APPENDED_FILE_TOKEN_VALUE];

	return OK;
}
int main(int argc, char *argv[])
{
	char * inventory_file_path;
	char * appended_file_path;
	status_t st;

	if ((st = validate_arguments(argc, argv, &inventory_file_path, &appended_file_path)) != OK)
		return st;

	printf("%s %s \n",inventory_file_path, appended_file_path );
	return OK;
}