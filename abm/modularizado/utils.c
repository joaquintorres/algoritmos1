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

	if (s == NULL || eof == NULL)
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
status_t split(const char * s,record_t * record ,char del)
{
	char * line; /*Se toma la cadena por copia.*/
	char * p ; /*Variable auxiliar*/
	char * aux ;		/*Variable auxiliar*/
	char * temp; /*Variable auxiliar*/
	char del_array[2]; /*strtok() toma una cadena de caracteres, no un char.*/

	del_array[0] = del;
	del_array[1] = '\0';

	if (s == NULL)
		return ERROR_NULL_POINTER;
	if (strdupl(s, &line))
		return ERROR_MEMORY;

	p = strtok(line, del_array);
	if (strdupl(p, &aux))
	{
		free(line);
		return ERROR_MEMORY;
	}
	record -> id = strtoul(aux,&temp,10);
	if (*temp && *temp != '\n')
		return ERROR_INPUT_FILE;
	
	p = strtok(NULL, del_array);
	if (strdupl(p, &(record -> barcode)))
	{
		free(line);
		return ERROR_MEMORY;
	}	

	p = strtok(NULL, del_array);
	if (strdupl(p, &(record -> description)))
	{
		free(line);
		return ERROR_MEMORY;
	}

	free(line); /*Se libera la copia.*/
	return OK;
}

/*Escribe sobre un archivo una estrucura record_t, en formato CSV*/
status_t export_record_to_CSV_file(FILE * target_file,record_t record,char field_del, char line_del)
{
	if (target_file == NULL)
		return ERROR_NULL_POINTER;

	fprintf(target_file, "%d%c", record.id, field_del);
	fprintf(target_file, "%s%c", record.barcode, field_del);
	fprintf(target_file, "%s", record.description);
	fputc(line_del, target_file);

	return OK;
}