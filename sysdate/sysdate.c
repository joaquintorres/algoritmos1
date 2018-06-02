#include <stdio.h>
#include <time.h>
#include "types.h"

status_t sysdate(char * format)
{
	time_t raw_time;
	struct tm * calendar_time;
	if (format == NULL)
		return ERROR_NULL_POINTER;
	if ((raw_time = time(NULL)) == -1)
		return ERROR_CLOCK;
	if((cal_ptr = localtime(&raw_time)) == NULL)
		return ERROR_NULL_POINTER;
	if (format == )
	return OK;
}