#include <stdio.h>
#include <time.h>
#include <string.h>
#include "types.h"
#include "formats.h"

status_t sysdate(char * format)
{
	time_t raw_time;
	struct tm * calendar_time;
	status_t st;
	if (format == NULL)
		return ERROR_NULL_POINTER;
	if ((raw_time = time(NULL)) == -1)
		return ERROR_CLOCK;
	if ((calendar_time = localtime(&raw_time)) == NULL)
		return ERROR_NULL_POINTER;
	
	if (!strcmp(format,FMT_DAY_MO_YR))
	{
		if ((st = print_as_day_month_year(calendar_time)) != OK)
			return st;
		return OK;
	}

	

	return OK;
}