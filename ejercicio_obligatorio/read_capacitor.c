/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: read_capacitor_value.c
	Descripción: Función ectura del valor de un capacitor, ingresado por el
	usuario. 
	****************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define UNIT_CAPACITANCE "[nF]"
#define MIN_CAPACITANCE_VALUE 0.00000000001
#define MAX_CAPACITANCE_VALUE 0.000047
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
	int scan_success;
	float result;
	if (msg == NULL || val == NULL)
	{
		return ERROR_NULL_POINTER;	
	}
	printf("%s %s \n", msg, UNIT_CAPACITANCE);
	scan_success = scanf("%f", &result);
	if (!scan_success || scan_success == EOF)
	{
		return ERROR_INVALID_INPUT;	
	}
	
	*val = result;
	*val *= MULTIPLIER_CAPACITANCE;
	if(*val < MIN_CAPACITANCE_VALUE || *val > MAX_CAPACITANCE_VALUE)
	{
		return ERROR_INVALID_INPUT;
	}
	return OK;
}

