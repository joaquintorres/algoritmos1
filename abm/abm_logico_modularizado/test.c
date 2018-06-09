#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INIT_CHOP 20
#define CHOP_SIZE 5
#define MAX_STR 100


#define FIELD_POSITION_FOR_ID 0
#define FIELD_POSITION_FOR_BARCODE 1
#define FIELD_POSITION_FOR_DESCRIPTION 2


typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_BAD_INPUT,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_DATA,
	ERROR_INVALID_KEY,
	ERROR_INPUT_FILE,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE
} status_t;

typedef enum{
	TRUE,
	FALSE
} bool_t;

typedef struct {
	size_t id;
	char * barcode;
	char * description;
} record_t;

status_t strdupl(const char * s, char ** t)
{
	size_t i;

	if (s == NULL || t == NULL)
		return ERROR_NULL_POINTER;
	if ((*t = (char *) malloc((strlen(s)+1)*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	for (i = 0;((*t)[i] = s[i]);i++);
	return OK;
}

status_t destroy_string_array(char *** p, size_t l)
{
	size_t i;

	if (p == NULL)
		return ERROR_NULL_POINTER;
	for (i = 0; i < l; i++)
	{
		free((*p)[i]);
		(*p)[i] = NULL;
	}/*Libera las cadenas*/
	free(*p); /*Libera el arreglo.*/
	*p = NULL;
	return OK;
}

status_t split(const char * s,char *** fields, char del, size_t * l) 
{
	char * line; /*Se toma la cadena por copia.*/
	char * q ; /*Variable auxiliar*/
	char * p ; /*Variable auxiliar*/
	size_t i;
	char del_array[2]; /*strtok() toma una cadena de caracteres, no un char.*/

	del_array[0] = del;
	del_array[1] = '\0';

	if (fields == NULL || s == NULL || l == NULL)
		return ERROR_NULL_POINTER;
	if (strdupl(s, &line))
	{
		*l = 0;
		return ERROR_MEMORY;

	}
	for (i = 0; line [i]; i++)
	{
		if (line[i] == del)
			(*l)++;	
	} /*Se cuenta la cantidad de delimitadores.*/
	(*l)++; /*La cantidad de campos es la cantidad de delimitadores más uno.*/
	if (((*fields) = (char **) malloc ((*l)*sizeof(char *)) ) == NULL)
	{
		free(line);
		*l = 0;
		free(*fields);
		return ERROR_MEMORY;
	}
	for (q = line, i = 0; (p = strtok(q, del_array)) != NULL;q =NULL, i++)
	{
			if (strdupl(p, &((*fields)[i])))
			{
				free(line);
				destroy_string_array(fields,i);
				*l = 0;
				return ERROR_MEMORY;
			}
	}

	free(line); /*Se libera la copia.*/
	return OK;
}

status_t make_record_from_string_array(record_t * record, char *** string_array, size_t size)
{
	char * temp;
	char * aux;

	if (record == NULL || string_array == NULL)
		return ERROR_NULL_POINTER;
	
	if (strdupl((*string_array)[FIELD_POSITION_FOR_ID], &aux))
		return ERROR_MEMORY;

	record -> id = strtoul(aux, &temp, 10);
	if (*temp && *temp != '\n')
		return ERROR_INVALID_KEY;
	if(strdupl((*string_array)[FIELD_POSITION_FOR_BARCODE],&(record -> barcode)))
		return ERROR_MEMORY;

	if(strdupl((*string_array)[FIELD_POSITION_FOR_DESCRIPTION],&(record -> description)))
		return ERROR_MEMORY;
	destroy_string_array(string_array,size);
	return OK;
}

int main(void)
{
	status_t st;
	char string[MAX_STR] = "123|dos|tres";
	record_t record ;
	char ** str_array;


	size_t l;
	if ((st = split(string, &str_array,'|', &l)) != OK)
		return st;
	
	printf("%s\n", str_array[0]);
	printf("%s\n", str_array[1]);
	printf("%s\n", str_array[2]);
	
	if ((st = make_record_from_string_array(&record, &(str_array),3))!= OK)
		return st;

	printf("%d\n", record.id);
	printf("%s\n", record.barcode);
	printf("%s\n", record.description);
	return OK;
}