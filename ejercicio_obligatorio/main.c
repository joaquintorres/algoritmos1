/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Archivo: main.c
	Descripción: Programa modularizado para el diseño de un 
	ecualizador gráfico. 
	****************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define CUTOFF_FREQUENCY 32
#define QUALITY_FACTOR 1.7

#define UNIT_RESISTANCE "[kOhm]"
#define UNIT_CAPACITANCE "[nF]"
#define MIN_RESISTANCE_VALUE 100
#define MAX_RESISTANCE_VALUE 
#define MULTIPLIER_RESISTANCE 0.001

#define MAX_STR 100

typedef  enum{
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_DATA,
	} status_t;


int main(void)
{
	double resistor_value_R1;
	double resistor_value_R2;

	double capacitor_value_C1;
	double capacitor_value_C2;

	/*Para nombrar las variables se asume que R1,R2,C1 y C2 son los nombres para los 
	componentes dados por el esquema circuital.*/

	read_resistor_value("Ingrese el valor del primer resistor: \n", resistor_value_R1);
	read_resistor_value("Ingrese el valor del segundo resistor: \n", resistor_value_R2);

	calculate_capacitor_value(resistor_value_R1, resistor_value_R2, capacitor_value_C1, capacitor_value_C2);

	print_component_value(resistor_value_R1, UNIT_RESISTANCE, COMPONENT_RESISTOR);
	print_component_value(resistor_value_R2, UNIT_RESISTANCE, COMPONENT_RESISTOR);

	print_component_value(capacitor_value_C1, UNIT_CAPACITANCE, COMPONENT_CAPACITOR);
	print_component_value(capacitor_value_C2, UNIT_CAPACITANCE, COMPONENT_CAPACITOR);

 	return 0;
}

status_t read_resistor_value(const char * msg, double * val)
{
	char str[MAX_STR];
	
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

	if (*temp && *temp != "\n")
	{
		return ERROR_INVALID_DATA;
	}

	if (*val < MIN_RESISTANCE_VALUE  || *val > MAX_RESISTANCE_VALUE )
	{
		return ERROR_INVALID_DATA;
	}

	/**************/

	*val *= MULTIPLIER_RESISTANCE;
	return OK;


}