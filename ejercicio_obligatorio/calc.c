/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.c
	Descripción: Programa modularizado para el diseño de un 
	ecualizador gráfico. 
	****************************************************************/

#include "main.h"

/*************************************************************
Toma los valores de dos resistores y calcula las capacitancias 
necesarias para el circuito del ecualizador. Las direcciones 
de las variables sobre donde se escriben los valores
de los capacitores se especifican como argumentos.
**************************************************************/
status_t calculate_capacitor_value(const double res_val_R1, const double res_val_R2, const double freq, const double q, double * cap_val_C1, double * cap_val_C2)
{
	double L;
	if(cap_val_C1 == NULL || cap_val_C2 == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	/*Estas validaciones son redundantes por cómo se obtuvieron los datos, pero la
	función tiene que ser a prueba de todo */
	if (res_val_R1 < MIN_RESISTANCE_VALUE || res_val_R1 > MAX_RESISTANCE_VALUE )
	{
		return ERROR_INVALID_DATA;
	}

	if (res_val_R2 < MIN_RESISTANCE_VALUE || res_val_R2 > MAX_RESISTANCE_VALUE )
	{
		return ERROR_INVALID_DATA;
	}
	
	if (freq < MIN_FREQUENCY_VALUE || freq > MAX_FREQUENCY_VALUE )
	{
		return ERROR_INVALID_DATA;
	}
	
	if (q < MIN_Q_FACTOR_VALUE || q > MAX_Q_FACTOR_VALUE )
	{
		return ERROR_INVALID_DATA;
	}
	/*****************************/
	
	/*Verificación de que no devuelve una inductancia equivalente negativa y que
	no se divide por 0*/
	if (res_val_R1 <= res_val_R2)
	{
		return ERROR_INVALID_DATA;
	}
	
	/*L inductancia equivalente---> paso intermedio*/
	 
	L = (q * res_val_R2)/(2* M_PI *freq);
	
	/*Valor del capacitor C1*/
	*cap_val_C1 = L / ((res_val_R1 - res_val_R2) * res_val_R2);

	if (*cap_val_C1 < MIN_CAPACITANCE_VALUE || *cap_val_C1 > MAX_CAPACITANCE_VALUE)
	{
		return ERROR_INVALID_RESULT;
	}

	/*Valor del capacitor C2*/
	*cap_val_C2 = 1 / ((2 * M_PI * freq) * (2 * M_PI * freq) * L);
	if (*cap_val_C2 < MIN_CAPACITANCE_VALUE || *cap_val_C2 > MAX_CAPACITANCE_VALUE)
	{
		return ERROR_INVALID_RESULT;
	}
	
	return OK;
}

