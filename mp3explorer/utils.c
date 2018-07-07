/*  ***************************************************************
  Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
  Trabajo Práctico N.° 2: Indexación automática de archivos MP3
  Alumno: Joaquín Torres
  Correo Electrónico: joaquintorres1997@gmail.com
  Archivo: utils.c
  Descripción: Programa que ordena un número arbitrario de archivos MP3
  por un criterio especificado por el usuario y los exporta ordenados en un 
  formato también determinado por el usuario.
  ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "types.h"

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

/*Compara cadenas de caracteres no arbitrariamente largas, pero sin hacer distinciones
entre minúsculas y mayúsculas. Así, "Pink Floyd", "pink floyd" y "PiNK fLoYD" son "iguales"*/ 
int strcasecomp(const char * a, const char * b)
{
	size_t i;
	char  low_a[MAX_STR]; /*se evita el uso de memoria estática, útil por*/
	char  low_b[MAX_STR];
	size_t len_a;
	size_t len_b;
	
	/*se crea una copia de los argumentos*/
	for (i = 0; (low_a[i] = a[i]); i++);
	for (i = 0; (low_b[i] = b[i]); i++);
	len_a = strlen(low_a);
	len_b = strlen(low_b);
	/*se pasan las copias a minúsculas*/
	for (i = 0; i < len_a; i++)
		low_a[i] = tolower(low_a[i]);
	for (i = 0; i < len_b; i++)
		low_b[i] = tolower(low_b[i]);
	return (strcmp(low_a,low_b));
}