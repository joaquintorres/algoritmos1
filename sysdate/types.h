#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_NUMBER_OF_ARGS,
	ERROR_INVALID_ARG,
	ERROR_INVALID_FLAG,
	ERROR_CLOCK /*Revisar significatividad*/
} status_t;

typedef struct 
{
	char ** messages;
	size_t size;
}error_dictionary_t;

#endif