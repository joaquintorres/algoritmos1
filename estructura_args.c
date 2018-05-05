#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUMBER_OF_ARGS 3
#define CMD_AMPLITUDE_TOKEN_NUMBER 1
#define CMD_AMPLITUDE_VALUE 2
#define CMD_AMPLITUDE_TOKEN "-A"
#define CMD_FREQUENCY_TOKEN_NUMBER 3
#define CMD_FREQUENCY_VALUE 4
#define CMD_FREQUENCY_TOKEN "-f"
#define CMD_PHASE_TOKEN_NUMBER 5
#define CMD_PHASE_TOKEN "-p"
#define CMD_PHASE_VALUE 6

typedef  enum{
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_ARGUMENTS,
	ERROR_INVALID_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_RESULT,
	ERROR_PROG_INVOCATION
	} status_t;
status_t validate_arguments(int argc, char * argv[], double * amp, double * freq, double * phase);

int main(int argc, char *argv[])
{
	double v;
	double amplitude;
	double frequency;
	double phase;
	if (validate_arguments(argc,argv,&amplitude,&frequency,&phase)!=OK)
	{
		fprintf(stderr, "%s\n", "Argumentos invalidos.");
		return ERROR_INVALID_ARGUMENTS;
	}
	
	return OK;
}
status_t validate_arguments(int argc, char * argv[], double * amp, double * freq, double * phase)
{
	char * tmp;
	if (amp == NULL || freq == NULL || phase == NULL)
		return ERROR_NULL_POINTER;
	if (argc != NUMBER_OF_ARGS)
		return ERROR_INVALID_NUMBER_OF_ARGUMENTS;
	
	if (!(strcmp(argv[CMD_AMPLITUDE_TOKEN_NUMBER], CMD_AMPLITUDE_TOKEN)))
		return ERROR_INVALID_FLAG;
	*amp = strtod(argv[CMD_AMPLITUDE_VALUE], &tmp);
	if (*tmp)
		return ERROR_PROG_INVOCATION;

	if (!(strcmp(argv[CMD_FREQUENCY_TOKEN_NUMBER], CMD_FREQUENCY_TOKEN)))
		return ERROR_INVALID_FLAG;
	*freq = strtod(argv[CMD_FREQUENCY_VALUE], &tmp);
	if (*tmp)
		return ERROR_PROG_INVOCATION;

	if (!(strcmp(argv[CMD_PHASE_TOKEN_NUMBER], CMD_PHASE_TOKEN)))
		return ERROR_INVALID_FLAG;
	*phase = strtod(argv[CMD_PHASE_VALUE], &tmp);
	if (*tmp)
		return ERROR_PROG_INVOCATION;
	
	if (*amp < 0 || *freq < 0 || *phase < 0)
	{
		return ERROR_INVALID_ARGUMENTS;
	}
	return OK;
}