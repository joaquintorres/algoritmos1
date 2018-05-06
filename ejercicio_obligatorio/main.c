/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.c
	Descripción: Programa modularizado para el diseño de un 
	ecualizador gráfico. 
	****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "components.h"
#include "messages.h"

int main (void)
{
	/*Para nombrar las variables se asume que R1,R2,C1 y C2 son los nombres para los 
	componentes dados por el esquema circuital.*/
	double resistor_R1;
	double resistor_R2;

	double capacitor_C1;
	double capacitor_C2;
	
	double frequency;
	double quality_factor;
	
	
	status_t st;
	
	/*Se verifica para todos los llamados a una función que el estado de salida sea exitoso.*/
	/******LECTURA*****/
	if ((st = read_resistor_value(USR_MSG_INPUT_RESISTOR_R1, &resistor_R1)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = read_resistor_value(USR_MSG_INPUT_RESISTOR_R2, &resistor_R2)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = read_frequency_value(USR_MSG_INPUT_FREQUENCY, &frequency)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = read_quality_factor_value(USR_MSG_INPUT_QUALITY_FACTOR, &quality_factor)) != OK)
	{
		print_error_message(st);
		return st;
	}
	/*******CÁLCULO*****/
	if ((st = calculate_capacitor_C1(resistor_R1, resistor_R2,frequency,quality_factor, &capacitor_C1)) != OK)
	{
		print_error_message(st);
		return st;
	}

	if ((st = calculate_capacitor_C2(resistor_R1, resistor_R2,frequency,quality_factor, &capacitor_C2)) != OK)
	{
		print_error_message(st);
		return st;
	}
	/*****IMPRESION*****/
	if ((st = print_resistor_value(USR_MSG_OUTPUT_RESISTOR_R1, resistor_R1)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_resistor_value(USR_MSG_OUTPUT_RESISTOR_R2, resistor_R2)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_frequency_value(USR_MSG_OUTPUT_FREQUENCY, frequency)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_quality_factor_value(USR_MSG_OUTPUT_QUALITY_FACTOR, quality_factor)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_capacitor_value(USR_MSG_OUTPUT_CAPACITOR_C1, capacitor_C1)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_capacitor_value(USR_MSG_OUTPUT_CAPACITOR_C2, capacitor_C2)) != OK)
	{
		print_error_message(st);
		return st;
	}

	return OK;
}




/**************************************
Recibe un estado de error e imprime el 
mensaje de error correspondiente.
***************************************/

status_t print_error_message(status_t err)
{
	stati char * errors[MAX_ERRORS] = {"",
										MSG_ERR_NULL_PTR,
	 									MSG_ERR_INVALID_DATA,
	 									MSG_ERR_INVALID_RESULT};
	fprintf(stderr,"%s\n", errors[err]);
	return err;
}