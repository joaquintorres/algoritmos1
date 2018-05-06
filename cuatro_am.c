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

typedef struct {
	double real;
	double imag;
} complex_t;

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_BAD_INPUT
} status_t;

status_t destroy_samples_array(complex_t **** array) 
{
	return OK;
}

/*
 * *samples[5] == *(samples[5]) == *(samples + 5);
 * (*samples)[5];
 */

status_t load_samples(FILE* input_file, complex_t **** samples, const size_t n)
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
			destroy_samples_array(samples);
			return ERROR_MEMORY;
		}
		for (j = 0; j < n; ++j)
		{
			if(((*samples)[i][j] = (complex_t *) malloc(n * sizeof(complex_t))) == NULL) /*MARK 3*/
			{
				destroy_samples_array(samples);
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
				destroy_samples_array(samples);
				return ERROR_BAD_INPUT;
			}
		}
	}
	return OK;
}

int main(void)
{
	return 0;
}