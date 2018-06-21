#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_NUMBER_OF_ARGS,
	ERROR_INVALID_ARG,
	ERROR_INVALID_FLAG
} status_t;

typedef enum {
	FMT_CSV,
	FMT_XML,
	FMT_HTML
} format_t;

#endif