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
#include "msg.h"

int main(void)
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
	if ((st = read_resistor_value(MSG_R1_IN, &resistor_R1)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = read_resistor_value(MSG_R2_IN, &resistor_R2)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = read_frequency_value(MSG_FREQ_IN, &frequency)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = read_quality_factor_value(MSG_QUALITY_FACTOR_IN, &quality_factor)) != OK)
	{
		print_error_message(st);
		return st;
	}
	/*******CÁLCULO*****/
	if ((st = calculate_capacitor_C1_value(resistor_R1, resistor_R2,frequency,quality_factor, &capacitor_C1)) != OK)
	{
		print_error_message(st);
		return st;
	}

	if ((st = calculate_capacitor_C2_value(resistor_R1, resistor_R2,frequency,quality_factor, &capacitor_C2)) != OK)
	{
		print_error_message(st);
		return st;
	}
	/*****ESCRITURA*****/
	if ((st = print_resistor_value(resistor_R1, MSG_R1_OUT)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_resistor_value(resistor_R2, MSG_R2_OUT)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_frequency_value(frequency, MSG_FREQ_OUT)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_quality_factor_value(quality_factor, MSG_QUALITY_FACTOR_OUT)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_capacitor_value(capacitor_C1, MSG_C1_OUT)) != OK)
	{
		print_error_message(st);
		return st;
	}
	
	if ((st = print_capacitor_value(capacitor_C2, MSG_C2_OUT)) != OK)
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
	char * errors[MAX_ERRORS] = {MSG_ERR_NULL_PTR, MSG_ERR_INVALID_DATA,MSG_ERR_INVALID_RESULT};
	printf("%s\n", errors[err + 1]);
	return err;
	/*Falta una validacion/manejo de otros errores. ARREGLAR/PENSAR URGENTE.*/
}