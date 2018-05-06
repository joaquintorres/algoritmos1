/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: capacitor.c
	Descripción: Función de lectura del valor de un capacitor, ingresado 
	por el usuario. 
	****************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define UNIT_CAPACITANCE "[nF]"
#define MIN_CAPACITOR_VALUE 0.00000000001
#define MAX_CAPACITOR_VALUE 0.000047
#define MULTIPLIER_CAPACITANCE 0.000000001


typedef  enum{
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_INPUT
	} status_t;

/*************PROTOTIPO*****************/
status_t read_capacitor_value(const char * msg, float * val);
/***************************************/

/**********************************************************
 Esta función toma como argumentos un mensaje para dar al
 usuario y la dirección de una variable sobre la que se escribe
 un valor de capacitancia ingresado por el usuario.Las unidades
 de entrada son definidas externamente y las unidades de salida
 son siempre en Farads. 
***********************************************************/
status_t read_capacitor_value (const char * msg, float * val)
{
	float user_input;
	int result;
	int c;
	
	if (msg == NULL || val == NULL)
		return ERROR_NULL_POINTER;	
	
	printf("%s %s \n", msg, UNIT_CAPACITANCE);
	result = scanf("%f", &user_input);
	if (!result || result == EOF)
		return ERROR_INVALID_INPUT;	
	/*Limpieza del buffer*/
	while ( (c = getchar()) != '\n' && c != EOF);
	if (c == EOF)
		return ERROR_INVALID_INPUT;
	
	*val = user_input;
	*val *= MULTIPLIER_CAPACITANCE;
	if(*val < MIN_CAPACITOR_VALUE || *val > MAX_CAPACITOR_VALUE)
		return ERROR_INVALID_INPUT;
	

	return OK;
}