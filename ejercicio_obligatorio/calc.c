/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: equalizer.c
	Descripción: Programa modularizado para el diseño de un 
	ecualizador gráfico. 
	****************************************************************/

#include <stdio.h>
#include <math.h>
#include "components.h"
#define M_PI		3.14159265358979323846

/*************************************************************
Toma los valores de dos resistores (R1<R2) y calcula las capacitancias 
necesarias para el circuito del ecualizador. Las direcciones 
de las variables sobre donde se escriben los valores
de los capacitores se especifican como argumentos.

C1 = L /((R1-R2)*R2)
**************************************************************/
status_t calculate_capacitor_C1(double res_val_R1,double res_val_R2,double freq,double q, double * cap_val_C1)
{
	double L;

	if(cap_val_C1 == NULL)
		return ERROR_NULL_POINTER;
	
	/*L inductancia equivalente---> paso intermedio*/
	 
	L = (q * res_val_R2)/(2* M_PI *freq);
	
	/*Valor del capacitor C1*/
	*cap_val_C1 = L / ((res_val_R1 - res_val_R2) * res_val_R2);

	if (*cap_val_C1 < MIN_CAPACITOR_VALUE || *cap_val_C1 > MAX_CAPACITOR_VALUE)
		return ERROR_INVALID_RESULT;
	
	return OK;
}
/****************************************
C2 = 1 / L(2*pi*f)^2
*****************************************/
status_t calculate_capacitor_C2(double res_val_R1, double res_val_R2, double freq, double q, double * cap_val_C2)
{
	if(cap_val_C2 == NULL)
		return ERROR_NULL_POINTER;

	/*Valor del capacitor C2*/
	*cap_val_C2 = 1 / ((2 * M_PI * freq) * (q * res_val_R2));
	if (*cap_val_C2 < MIN_CAPACITOR_VALUE || *cap_val_C2 > MAX_CAPACITOR_VALUE)
		return ERROR_INVALID_RESULT;
	
	return OK;
}

