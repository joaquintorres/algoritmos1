/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: io.c
	Descripción: Programa modularizado para el diseño de un 
	ecualizador gráfico. 
	****************************************************************/

#include "main.h"

/**********************************************************
 Esta función toma como argumentos un mensaje para dar al
 usuario y la dirección de una variable sobre la que se escribe
 un valor de resistencia ingresado por el usuario.Las unidades
 de entrada son definidas externamente y las unidades de salida
 son siempre en Ohms. 
***********************************************************/
status_t read_resistor_value(const char * msg, double * val)
{
	char str[MAX_STR];
	char * temp;

	if (msg == NULL || val == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	
	printf("%s %s \n", msg, UNIT_RESISTANCE);


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
	return OK;

}
/**Se repite la misma función para la frecuencia y el factor de calidad en
lugar de utilizar funciones diferenciadas, en el caso de que se quiera
modificar el comportamiento con respecto a estas variables**/
status_t read_frequency_value(const char * msg, double * val)
{
	char str[MAX_STR];
	char * temp;

	if (msg == NULL || val == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	
	printf("%s %s \n", msg, UNIT_FREQUENCY);


	if (fgets(str,MAX_STR, stdin) == NULL)
	{
		return ERROR_INVALID_DATA;
	}

	*val = strtod(str, &temp);

	if (*temp && *temp != '\n')
	{
		return ERROR_INVALID_DATA;
	}

	*val *= MULTIPLIER_FREQUENCY;

	if (*val < MIN_FREQUENCY_VALUE  || *val > MAX_FREQUENCY_VALUE || *val == 0)
	{
		return ERROR_INVALID_DATA;
	}
	return OK;

}
status_t read_q_factor_value(const char * msg, double * val)
{
	char str[MAX_STR];
	char * temp;

	if (msg == NULL || val == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	
	printf("%s \n", msg);


	if (fgets(str,MAX_STR, stdin) == NULL)
	{
		return ERROR_INVALID_DATA;
	}

	*val = strtod(str, &temp);

	if (*temp && *temp != '\n')
	{
		return ERROR_INVALID_DATA;
	}

	if (*val < MIN_Q_FACTOR_VALUE  || *val > MAX_Q_FACTOR_VALUE || *val == 0)
	{
		return ERROR_INVALID_DATA;
	}
	return OK;

}

/****************************************************************
Recibe el valor del componente en la unidad SI correspondiente (sin
prefijos, por ejemplo Ohms o Farads), una cadena de caracteres que
especifica la unidad en la que se debe mostrar el resultado al usuario,
el multiplicador de la correspondiente unidad a la nueva y el mensaje
junto al cual se muestra el resultado.
****************************************************************/
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

