/*-Se tiene un programa que carga una matriz de punteros a complejos de n por n elementos (tomar esto como constante).
 * El prototipo de la función que carga esta matriz de muestras es:
 * status_t load_samples(complex_t ___ samples, size_t ___ n);
 * a) Escribir la definición del tipo complex_t.
 * b) Definir la función load_samples().
 * c) Escribir la definición de la función load_samples() con el siguiente prototipo:
 * status_t load_samples(____ FILE ___ input_file, _____ complex_t ____ samples, ____ size_t ____ n)
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/***Argumentos por línea de Órdenes **/
#define MIN_ARGUMENTS 5
#define MAX_ARGUMENTS 5

#define CMD_ARG_FILE_TOKEN_POSITION 1
#define CMD_ARG_FILE_TOKEN_VALUE 2
#define CMD_ARG_FILE_FLAG "-f"

#define CMD_ARG_MATRIX_DIMENSION_TOKEN_POSITION 3
#define CMD_ARG_MATRIX_DIMENSION_TOKEN_VALUE 4
#define CMD_ARG_MATRIX_DIMENSION_FLAG "-n"


typedef struct {
	double real;
	double imag;
} complex_t;

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

/*char * program_name;*/

status_t destroy_samples_array(complex_t **** array, size_t * n) 
{
	size_t i;
	size_t j;
	for (i = 0; i < *n ; ++i)
	{
		for (j = 0; j < *n; ++j)
		{
			free((*array)[i][j]);
			(*array)[i][j] = NULL;
		}
		free((*array)[i]);
		(*array)[i] = NULL;
	}
	free(*array);
	*array = NULL;
	*n = 0;
	return OK;
}

/*
 * *samples[5] == *(samples[5]) == *(samples + 5);
 * (*samples)[5];
 */

status_t load_samples(FILE* input_file, complex_t **** samples, size_t n)
{
	size_t i, j;

	if (samples == NULL || input_file == NULL)
		return ERROR_NULL_POINTER;

	if ((*samples = (complex_t ***) malloc(n * sizeof(complex_t **))) == NULL) /*MARK 1*/
		return ERROR_MEMORY;
	for (i = 0; i < n; ++i)
	{
		if (((*samples)[i] = (complex_t **) malloc(n * sizeof(complex_t *))) == NULL) /*MARK 2*/
		{
			destroy_samples_array(samples, &n);
			return ERROR_MEMORY;
		}
		for (j = 0; j < n; ++j)
		{
			if(((*samples)[i][j] = (complex_t *) malloc(n * sizeof(complex_t))) == NULL) /*MARK 3*/
			{
				destroy_samples_array(samples, &n);
				return ERROR_MEMORY;
			}
		}

	}

	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			if (!fread((*samples)[i][j], sizeof(complex_t), 1, input_file))
			{
				destroy_samples_array(samples, &n);
				return ERROR_BAD_INPUT;
			}
		}
	}
	return OK;
}
status_t print_complex_pointer_array(complex_t *** array, size_t n)
{
	size_t i;
	size_t j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++i)
			printf("(%f %c %f) \n", array[i][j]->real, ',', array[i][j]->imag);
	return OK;
}
status_t validate_arguments(int argc, char * argv[], size_t * samples_size, char ** file_path)
{
	char * temp;
	if (samples_size == NULL || file_path == NULL)
		return ERROR_NULL_POINTER;
	if(argc > MAX_ARGUMENTS || argc < MIN_ARGUMENTS)
		return ERROR_NUMBER_OF_ARGUMENTS;
	if (strcmp(argv[CMD_ARG_FILE_TOKEN_POSITION], CMD_ARG_FILE_FLAG))
		return ERROR_INVALID_FLAG; 
	*file_path = argv[CMD_ARG_FILE_TOKEN_VALUE];
	
	if (strcmp(argv[CMD_ARG_MATRIX_DIMENSION_TOKEN_POSITION], CMD_ARG_MATRIX_DIMENSION_FLAG))
		return ERROR_INVALID_FLAG;
	*samples_size = strtoul(argv[CMD_ARG_MATRIX_DIMENSION_TOKEN_VALUE], &temp, 10);
	if (*temp != '\0')
		return ERROR_INVALID_NUMBER;
	return OK;
}

int main(int argc, char * argv[])
{	
	status_t st;
	complex_t *** samples;
	size_t samples_size; /*= argv[CMD_ARG_MATRIX_DIMENSION_TOKEN_VALUE];*/
	char * file_path; /* = argv[CMD_ARG_FILE_TOKEN_VALUE];*/
	FILE * file_pointer;
	/*program_name = argv[0];*/
	if ((st = validate_arguments(argc, argv, &samples_size, &file_path)) != OK)
		return st;

	if ((file_pointer = fopen(file_path, "rb")) == NULL)
		return ERROR_FILE;

	st = load_samples(file_pointer, &samples, samples_size);
	if (st != OK)
		return st;

	if (fclose(file_pointer) == EOF)
		return ERROR_FILE;

	st = print_complex_pointer_array(samples, samples_size);
	if (st != OK)
		return st;

	st = destroy_samples_array(&samples, &samples_size);
	if (st != OK)
		return st;

	return OK;
}