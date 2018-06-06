#ifndef PROCESS_ADDITION_RECORDS__H
#define PROCESS_ADDITION_RECORDS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"

status_t process_addition_records(FILE * old_file,FILE * mod_file, FILE * new_file, char line_del, char field_del);
#endif