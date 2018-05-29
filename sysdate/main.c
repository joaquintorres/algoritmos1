#include <stdio.h>
#include <string.h>
#include <time.h>

/*MENSAJES DE ERROR*/
#define ERR_MSG_NULL_POINTER "Ha ocurrido un error por pasaje de puntero nulo."
#define ERR_MSG_NUMBER_OF_ARGS "Cantidad de argumentos inválida."
#define ERR_MSG_FLAG "Flag incorrecta."
#define ERR_MSG_INVALID_ARGUMENT "Argumento incorrecto."
#define USR_MSG_USAGE "La sintaxis correcta es ./sysdate -fmt <format> o sysdate -fmt <format> si el ejecutable se encuentra en PATH."
#define USR_MSG_USAGE_FMT "Los formatos aceptados son: "
/*******************/

/*ARGUMENTOS*/
#define MIN_NUMBER_OF_ARGS 3
#define MAX_NUMBER_OF_ARGS 3

#define CMD_ARG_FORMAT_TOKEN_POSITION 1
#define CMD_ARG_FORMAT_TOKEN_VALUE 2
#define CMD_ARG_FORMAT_FLAG "-fmt"

#define FMT_DAY_MO_YR "DDMMAAAA" 
#define FMT_YR_DAY "AAAADDD" /*Día (sobre los 365) del año.*/
#define FMT_YR_MO_DAY "AAAAMMDD"
#define FMT_YR_MO_DAY_HR_MIN_SEC "AAAAMMDDHHmmSS" /*El día del mes.*/
#define FMT_YR_DAY_HR_MIN_SEC "AAAADDDHHmmSS" /*El día del año.*/
/************/
typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_NUMBER_OF_ARGS,
	ERROR_INVALID_ARG,
	ERROR_INVALID_FLAG
} status_t;

/*PROTOTIPOS*/
status_t validate_arguments(size_t argc, char * argv[], char ** format);
/************/

int main(int argc, char * argv[])
{
	char * format;
	status_t st;

	if ((st = validate_arguments(argc,argv,&format)) != OK)
		return st;
	printf("%s\n", format);
	return OK;
}

status_t validate_arguments(size_t argc, char * argv[], char ** format)
{
	char * arg_value_fmt;
	arg_value_fmt = argv[CMD_ARG_FORMAT_TOKEN_VALUE];
	if (argv == NULL || format == NULL)
	{
		fprintf(stderr, "%s\n", ERR_MSG_NULL_POINTER);
		return ERROR_NULL_POINTER;
	}
	if (argc < MIN_NUMBER_OF_ARGS || argc > MAX_NUMBER_OF_ARGS)
	{
		fprintf(stderr, "%s\n", ERR_MSG_NUMBER_OF_ARGS);
		fprintf(stderr, "%s\n", USR_MSG_USAGE);
		return ERROR_INVALID_NUMBER_OF_ARGS;
	}
	if (strcmp(argv[CMD_ARG_FORMAT_TOKEN_POSITION], CMD_ARG_FORMAT_FLAG))
	{
		fprintf(stderr, "%s\n", ERR_MSG_FLAG);
		fprintf(stderr, "%s\n", USR_MSG_USAGE);
		return ERROR_INVALID_FLAG;
	}
	if (strcmp(arg_value_fmt, FMT_YR_DAY) && strcmp(arg_value_fmt, FMT_DAY_MO_YR) && strcmp(arg_value_fmt, FMT_YR_MO_DAY) && strcmp(arg_value_fmt, FMT_YR_DAY_HR_MIN_SEC) && strcmp(arg_value_fmt, FMT_YR_MO_DAY_HR_MIN_SEC))
	{
		fprintf(stderr, "%s\n", ERR_MSG_INVALID_ARGUMENT);
		fprintf(stderr, "%s\n %s\n %s\n %s\n %s\n %s\n",USR_MSG_USAGE_FMT, FMT_YR_DAY, FMT_DAY_MO_YR, FMT_YR_MO_DAY, FMT_YR_DAY_HR_MIN_SEC, FMT_YR_MO_DAY_HR_MIN_SEC);
		return ERROR_INVALID_ARG;	
	}
	*format = argv[CMD_ARG_FORMAT_TOKEN_VALUE];
	return OK;
}