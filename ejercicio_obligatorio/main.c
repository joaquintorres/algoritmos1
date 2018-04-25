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

#define M_PI 3.14159265358979323846
#define CUTOFF_FREQUENCY 32
#define QUALITY_FACTOR 1.7

#define UNIT_RESISTANCE "[kOhm]"
#define UNIT_CAPACITANCE "[nF]"
#define UNIT_FREQUENCY "[Hz]"

#define MIN_RESISTANCE_VALUE 1
#define MAX_RESISTANCE_VALUE 10000000
#define MULTIPLIER_RESISTANCE 1000

#define MIN_CAPACITANCE_VALUE 0.00000000001
#define MAX_CAPACITANCE_VALUE 0.000047
#define MULTIPLIER_CAPACITANCE 1000000000

#define MAX_STR 100

typedef  enum{
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_DATA,
	ERROR_INVALID_RESULT
	} status_t;

/***PROTOTIPOS**********/
status_t read_resistor_value(const char * msg, double * val);
status_t calculate_capacitor_value(const double res_val_R1, const double res_val_R2, double * cap_val_C1, double * cap_val_C2);
status_t print_component_value(double val, const char * unit, const double multiplier, const char * msg);
/***********************/


int main(void)
{
	double resistor_value_R1;
	double resistor_value_R2;

	double capacitor_value_C1;
	double capacitor_value_C2;

	/*Para nombrar las variables se asume que R1,R2,C1 y C2 son los nombres para los 
	componentes dados por el esquema circuital.*/

	read_resistor_value("Ingrese el valor del primer resistor: ", &resistor_value_R1);
	read_resistor_value("Ingrese el valor del segundo resistor: ", &resistor_value_R2);

	calculate_capacitor_value(resistor_value_R1, resistor_value_R2, &capacitor_value_C1, &capacitor_value_C2);

	print_component_value(resistor_value_R1, UNIT_RESISTANCE, MULTIPLIER_RESISTANCE, "Valor del resistor R1: ");
	print_component_value(resistor_value_R2, UNIT_RESISTANCE, MULTIPLIER_RESISTANCE, "Valor del resistor R2: ");

	print_component_value(capacitor_value_C1, UNIT_CAPACITANCE, MULTIPLIER_CAPACITANCE, "Valor del capacitor C1: ");
	print_component_value(capacitor_value_C2, UNIT_CAPACITANCE, MULTIPLIER_CAPACITANCE, "Valor del capacitor C2: ");

 	return 0;
}

status_t read_resistor_value(const char * msg, double * val)
{
	char str[MAX_STR];
	char * temp;

	if (msg == NULL || val == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	
	printf("%s %s \n", msg, UNIT_RESISTANCE);
	fgets(str,MAX_STR, stdin);

	/*VALIDACIONES*/

	if (fgets(str,MAX_STR, stdin) == NULL)
	{
		return ERROR_INVALID_DATA;
	}

	*val = strtod(str, &temp);

	if (*temp && *temp != '\n')
	{
		return ERROR_INVALID_DATA;
	}

	*val *= MULTIPLIER_RESISTANCE;

	if (*val < MIN_RESISTANCE_VALUE  || *val > MAX_RESISTANCE_VALUE || *val == 0)
	{
		return ERROR_INVALID_DATA;
	}

	/**************/

	
	return OK;

}

status_t calculate_capacitor_value(const double res_val_R1, const double res_val_R2, double * cap_val_C1, double * cap_val_C2)
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
	/*****************************/
	
	/*Verificación de que no devuelve una inductancia equivalente negativa y que
	no se divide por 0*/
	if (res_val_R1 <= res_val_R2)
	{
		return ERROR_INVALID_DATA;
	}
	
	/*L inductancia equivalente---> paso intermedio*/
	 
	L = (QUALITY_FACTOR * res_val_R2)/(2* M_PI *CUTOFF_FREQUENCY);
	
	/*Valor del capacitor C1*/
	*cap_val_C1 = L / ((res_val_R1 - res_val_R2) * res_val_R2);
	if (*cap_val_C1 < MIN_CAPACITANCE_VALUE || *cap_val_C1 > MAX_CAPACITANCE_VALUE)
	{
		return ERROR_INVALID_RESULT;
	}

	/*Valor del capacitor C2*/
	*cap_val_C2 = 1 / ((2 * M_PI * CUTOFF_FREQUENCY) * (2 * M_PI * CUTOFF_FREQUENCY) * L);
	if (*cap_val_C2 < MIN_CAPACITANCE_VALUE || *cap_val_C2 > MAX_CAPACITANCE_VALUE)
	{
		return ERROR_INVALID_RESULT;
	}

	return OK;
}

status_t print_component_value(double val, const char * unit, const double multiplier, const char * msg)
{
	if (unit == NULL || msg == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	if (multiplier <= 0)
	{
		return ERROR_INVALID_DATA;
	}

	printf("%s %.2f %s \n", msg, val/multiplier, unit);
	return OK;
}
