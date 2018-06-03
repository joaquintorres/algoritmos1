#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_POSITION 0
#define BARCODE_POSITION 1
#define DESCRIPTION_POSITION 2

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_SPLIT,
	ERROR_BAD_INPUT,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_DATA,
	ERROR_INPUT_FILE,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE
} status_t;

typedef struct {
	size_t id;
	char * barcode;
	char * description;
} item_t;

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

status_t split(const char * s,item_t * item ,char del, size_t * l) /*Falta pasarlo a status_t y reemplazar ERROR_SPLIT*/
{
	char * line; /*Se toma la cadena por copia.*/
	char ** fields;
	char * q; /*Variable auxiliar*/
	char * p; /*Variable auxiliar*/
	char * temp;
	size_t i;
	char del_array[2]; /*strtok() toma una cadena de caracteres, no un char.*/

	del_array[0] = del;
	del_array[1] = '\0';

	if (s == NULL || l == NULL)
		return ERROR_NULL_POINTER;
	if (strdupl(s, &line))
	{
		*l = 0;
		return ERROR_MEMORY;

	}
	for (i = 0; line[i]; i++)
	{
		if (line[i] == del)
			(*l)++;	
	} /*Se cuenta la cantidad de delimitadores.*/
	(*l)++; /*La cantidad de campos es la cantidad de delimitadores más uno.*/

	if ((fields = (char **) malloc((*l) * sizeof(char *)) ) == NULL)
	{
		free(line);
		*l = 0;
		free(fields);
		fprintf(stderr, "%s\n", "YABBADABADOO");
		return ERROR_MEMORY;
	}
	for (q = line, i = 0; (p = strtok(q, del_array)) != NULL;q =NULL, i++)
	{
			if (strdupl(p, &(fields[i])))
			{
				free(line);
				destroy_string_array(&fields,i);
				*l = 0;
				return ERROR_MEMORY;
			}
	}

	free(line); /*Se libera la copia.*/

	item->id = strtoul(fields[ID_POSITION],&temp,10);
	if (*temp && *temp != '\n')
		return ERROR_INPUT_FILE;
	item->barcode = fields[BARCODE_POSITION];
	item->description = fields[DESCRIPTION_POSITION];
	return OK;
}

int main(void)
{
	char * string;
	char * string_2;
	item_t str_item;
	item_t str_item_2;
	size_t l;
	size_t n;
	status_t st;

	string = "111212|BAR$$$$$$$$$$$$$$CODE|description.";
	string_2 = "111212|sddddssds|sddssddsas.";

	if ((st = split(string, &str_item, '|', &l)) != OK)
		return st;

	/*if ((st = split(string_2, &str_item_2, '|', &n)) != OK)
		return st;
	*/
/*	if (str_item.id == str_item_2.id)
	{
		str_item.barcode = str_item_2.barcode;
		str_item.description = str_item_2.description;
	}
*/
	printf("%s\n", str_item.barcode);
	printf("%s\n", str_item.description);
/*	
	printf("%s\n", str_item_2.barcode);
	printf("%s\n", str_item_2.description);
*/
	return OK;
}