#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ARGUMENTS 5
#define MAX_ARGUMENTS 5

#define CMD_ARG_INVENTORY_FILE_TOKEN_POSITION 1
#define CMD_ARG_INVENTORY_FILE_TOKEN_VALUE 2
#define CMD_ARG_INVENTORY_FILE_FLAG "-i"

#define CMD_ARG_APPENDED_FILE_TOKEN_POSITION 3
#define CMD_ARG_APPENDED_FILE_TOKEN_VALUE 4
#define CMD_ARG_APPENDED_FILE_FLAG "-a"

#define TEMP_FILENAME "salida.tmp"
#define INIT_CHOP 20
#define CHOP_SIZE 5
typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_BAD_INPUT,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_NUMBER,
	ERROR_INPUT_FILE,
	ERROR_DISK_SPACE
} status_t;

typedef enum{
	TRUE,
	FALSE
} bool_t;

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

status_t read_line(char ** s, bool_t * eof)
{
	size_t used_size;
	size_t alloc_size;
	char c;
	char * aux;
	if (s == NULL || eof == NULL)
		return ERROR_NULL_POINTER;
	if ((*s = (char *) malloc(INIT_CHOP*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	alloc_size = INIT_CHOP;
	used_size = 0;
	while ((c = getchar())!= '\n' && c != EOF)
	{
		if (used_size == alloc_size - 1)
		{
			if ((aux = (char *) realloc(s, (alloc_size + CHOP_SIZE)*sizeof(char))) == NULL)
			{
				free(*s);
				*s = NULL;
				return ERROR_MEMORY;
			}
			*s = aux;
			alloc_size += CHOP_SIZE;
		}
		(*s)[used_size++] = c;
	}
	*eof = (c == EOF) ? TRUE:FALSE;
	return OK;	
}

int main(int argc, char *argv[])
{
	char * inventory_file_path;
	char * appended_file_path;
	char * line;
	FILE * inventory_file_ptr;
	FILE * appended_file_ptr;
	FILE * crud_file_ptr;  /*Puntero al archivo resultante de aplicar ABM (o CRUD por sus siglas en inglés)*/
	status_t st;
	bool_t eof; /*booleano que indica si en la lectura se llegó a EOF*/
	if ((st = validate_arguments(argc, argv, &inventory_file_path, &appended_file_path)) != OK)
		return st;
	/*APERTURA*/
	if ((inventory_file_ptr = fopen(inventory_file_path,"rt")) == NULL)
		return ERROR_INPUT_FILE;
	if ((appended_file_ptr = fopen(appended_file_path,"rt")) == NULL)
	{
		fclose(inventory_file_ptr);
		return ERROR_INPUT_FILE;
	}
	if ((crud_file_ptr = fopen(TEMP_FILENAME,"wt")) == NULL)
	{
		fclose(inventory_file_ptr);
		fclose(appended_file_ptr);
		return ERROR_INPUT_FILE;
	}
	/*LECTURA*/
	eof = FALSE;
	while (eof == FALSE)
	{
		/*if((st = read_line(&line,&eof)) !=OK)
			return st;*/
		read_line
		puts(line);
		free(line);
	}
	/*ABM*/

	/*CIERRE*/
	fclose(inventory_file_ptr);
	fclose(appended_file_ptr);
	if ((fclose(crud_file_ptr)) == EOF)
		return ERROR_DISK_SPACE;


	return OK;
}