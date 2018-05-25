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
#define LINE_DELIMITER '|'
#define FIELD_DELIMITER ','

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

/*Valida los argumentos pasados por línea de órdenes y devuelve por puntero las variables validadas.*/
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

/*Lee líneas de un archivo, separando una línea con algún delimitador pasado como argumento.
La línea se devuelve por puntero como una cadena de caracteres. Además, se devuelve un booleano
por puntero indicando si se llegó al EOF o no (con TRUE y FALSE respectivamente).*/
status_t read_line_from_file(FILE * source_file,const char del,char ** s, bool_t * eof)
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
	while ((c = fgetc(source_file))!= del && c != EOF)
	{
		if (used_size == alloc_size - 1)
		{
			if ((aux = (char *) realloc(*s, (alloc_size + CHOP_SIZE)*sizeof(char))) == NULL)
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
/*Recibe una cadena de caracteres y devuelve por puntero la misma cadena copiada.*/
status_t strdupl(const char * s, char ** t)
{
	if (s == NULL || t == NULL)
		return ERROR_NULL_POINTER;
	if ((*t = (char *) malloc((strlen(s)+1)*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	strcpy(*t,s);
	return OK;
}
/*Destruye un arreglo de cadenas de caracteres.*/
status_t destroy_string_array(char *** p, size_t l)
{
	size_t i;
	if (p == NULL)
		return ERROR_NULL_POINTER;
	for (i = 0; i < l; i++)
	{
		free((*p)[i]);
		(*p)[i] = NULL;
	}/*Borra las cadenas*/
	free(*p); /*Borra el arreglo.*/
	*p = NULL;
	return OK;
}

/*Recibe una línea separada en campos por un delimitador pasado como argumento.
Devuelve por puntero un arreglo de cadenas que contiene en cada elemento uno de los campos originales
y una variable que contiene la cantidad de campos.*/
char ** split(const char * s, char del, size_t * l)
{
	char * line; /*Se toma la cadena por copia.*/
	char ** fields;
	char * q; /*Variable auxiliar*/
	char * p; /*Variable auxiliar*/
	size_t i;
	char del_array[2]; /*strtok() toma una cadena de caracteres, no un char.*/

	del_array[0] = del;
	del_array[1] = '\0';

	if (s == NULL || l == NULL)
		return NULL;
	if (strdupl(s, &line))
	{
		*l = 0;
		return NULL;
	}
	for (i = 0; line [i]; i++)
	{
		if (line[i] == del)
			(*l)++;	
	} /*Se cuenta la cantidad de delimitadores.*/
	(*l)++; /*La cantidad de campos es la cantidad de delimitadores más uno.*/
	if ((fields = (char **) malloc ((*l)*sizeof(char *)) ) == NULL)
	{
		free(line);
		*l = 0;
		free(fields);
		return NULL;
	}
	for (q = line,i = 0; (p = strtok(line, del_array)) != NULL; q = NULL,i++)
	{
			if (strdupl(p, &fields[i]))
			{
				free(line);
				destroy_string_array(&fields,i);
				*l = 0;
				return NULL;
			}
	}
	free(line); /*Se libera la copia.*/
	return fields;
}

int main(int argc, char *argv[])
{
	char * inventory_file_path;
	char * appended_file_path;
	char * line;
	char ** string_array; 
	FILE * inventory_file_ptr;
	FILE * appended_file_ptr;
	FILE * crud_file_ptr;  /*Puntero al archivo resultante de aplicar ABM (o CRUD por sus siglas en inglés)*/
	status_t st;
	bool_t eof; /*booleano que indica si en la lectura se llegó a EOF*/
	size_t string_array_length;
	size_t i;

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
		if((st = read_line_from_file(inventory_file_ptr,LINE_DELIMITER,&line,&eof)) !=OK)
			return st;
		string_array = split(line,LINE_DELIMITER,&string_array_length);
		for (i = 0; i < string_array_length; ++i)
			fprintf(crud_file_ptr, "%s\n", string_array[i]);
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