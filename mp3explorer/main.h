#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include "types.h"

/*ARGUMENTOS*/
#define MIN_NUMBER_OF_ARGS 8

#define CMD_ARG_FORMAT_TOKEN_POSITION 1
#define CMD_ARG_FORMAT_TOKEN_VALUE 2
#define CMD_ARG_FORMAT_FLAG "-fmt"

#define CMD_ARG_SORT_CRITERION_TOKEN_POSITION 3
#define CMD_ARG_SORT_CRITERION_TOKEN_VALUE 4
#define CMD_ARG_SORT_CRITERION_FLAG "-sort"

#define CMD_ARG_OUTPUT_TOKEN_POSITION 5
#define CMD_ARG_OUTPUT_TOKEN_VALUE 6
#define CMD_ARG_OUTPUT_FLAG "-o"
/*FORMATOS DE SALIDA*/
#define MAX_FORMATS 3

#define ARG_FMT_CSV "csv"
#define ARG_FMT_XML "xml"
#define ARG_FMT_HTML "html"
/*CRITERIOS DE ORDENAMIENTO*/
#define MAX_SORT_CRITERIA 3

#define ARG_SORT_NAME "name"
#define ARG_SORT_ARTIST "artist"
#define ARG_SORT_GENRE "genre"

/*PROTOTIPOS*/status_t validate_arguments(size_t argc, char * argv[], format_t * format, sort_t * sort, char * output_filename[], char ***input_files, size_t * len);
#endif