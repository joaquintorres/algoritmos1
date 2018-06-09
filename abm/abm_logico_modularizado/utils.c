/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: utils.c
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "types.h"
/*Lee líneas de un archivo, separando una línea con algún delimitador pasado como argumento.
La línea se devuelve por puntero como una cadena de caracteres. Además, se devuelve un booleano
por puntero indicando si se llegó al EOF o no (con TRUE y FALSE respectivamente).*/
status_t read_line_from_file(FILE * file, char del, char ** s, bool_t * eof)
{
	size_t used_size;
	size_t alloc_size;
	int c;
	char * aux;

	puts("\t\t read_line_from_file()");
	if (s == NULL || eof == NULL || file == NULL)
		return ERROR_NULL_POINTER;
	if ((*s = (char *) malloc(INIT_CHOP*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	alloc_size = INIT_CHOP;
	used_size = 0;
	while ((c = fgetc(file))!= del && c != EOF)
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
	size_t i;

	if (s == NULL || t == NULL)
		return ERROR_NULL_POINTER;
	if ((*t = (char *) malloc((strlen(s)+1)*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	for (i = 0;((*t)[i] = s[i]);i++);
	return OK;
}
/*Recibe una línea separada en campos por un delimitador pasado como argumento.
Devuelve por puntero un arreglo de cadenas que contiene en cada elemento uno de los campos originales
y una variable que contiene la cantidad de campos.*/
status_t split(const char * s,char *** fields, char del, size_t * l) 
{
	char * line = NULL; /*Se toma la cadena por copia.*/
	char * q = NULL ; /*Variable auxiliar*/
	char * p = NULL; /*Variable auxiliar*/
	size_t i;
	char del_array[2]; /*strtok() toma una cadena de caracteres, no un char.*/

	del_array[0] = del;
	del_array[1] = '\0';

	puts("\t\t split()");
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
		puts("\t\t\t strtok()");
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
/*Destruye un arreglo de cadenas de caracteres.*/
status_t destroy_string_array(char *** p, size_t l)
{
	size_t i;

	puts("destroy_string_array");
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

/*Pasa un arreglo de cadenas a una estructura record_t, destruye la estructura*/
status_t make_record_from_string_array(record_t * record, char ** string_array)
{
	char * temp;
	char * aux;

	puts("\t\t make_record_from_string_array");
	if (record == NULL || string_array == NULL)
		return ERROR_NULL_POINTER;
	
	if (strdupl(string_array[FIELD_POSITION_FOR_ID], &aux))
		return ERROR_MEMORY;

	record -> id = strtoul(aux, &temp, 10);
	if (*temp && *temp != '\n')
		return ERROR_INVALID_KEY;
	if(strdupl(string_array[FIELD_POSITION_FOR_BARCODE],&(record -> barcode)))
		return ERROR_MEMORY;

	if(strdupl(string_array[FIELD_POSITION_FOR_DESCRIPTION],&(record -> description)))
		return ERROR_MEMORY;

	return OK;
}

status_t read_record_from_CSV_file(record_t * record, FILE * file, char field_del, char line_del, bool_t * eof)
{
	char * line;
	char ** aux_str_array;
	size_t l;
	status_t st;
	bool_t aux_eof;
	*eof = FALSE;

	puts("\t read_record_from_CSV_file()");
	if (record == NULL || file == NULL)
		return ERROR_NULL_POINTER;

	if ((st = read_line_from_file(file, line_del, &line, &aux_eof)) != OK)
		return st;
	
	if ((st = split(line, &aux_str_array,field_del, &l)) != OK)
		return st;

	if((st = make_record_from_string_array(record,aux_str_array))!= OK)
		return st;
	
	destroy_string_array(&aux_str_array,l);
	free(line);
	if(aux_eof == TRUE)
		*eof = TRUE;	
	
	return OK;
}

/*Escribe sobre un archivo una estrucura record_t, en formato CSV*/
status_t export_record_to_CSV_file(record_t record,FILE * target_file,char field_del)
{
	if (target_file == NULL)
		return ERROR_NULL_POINTER;

	fprintf(target_file, "%d%c", record.id, field_del);
	fprintf(target_file, "%s%c", record.barcode, field_del);
	fprintf(target_file, "%s", record.description);
	fputc('\n', target_file);

	return OK;
}