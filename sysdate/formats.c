#include <stdio.h>
#include <time.h>
#include "types.h"
#include "formats.h"

status_t print_as_day_month_year(struct tm * time)
{
	if (time == NULL)
		return ERROR_NULL_POINTER;
	printf("%02d %02d %04d\n", time -> tm_mday, (time -> tm_mon) +1, (time ->tm_year) + 1900);
	return OK;
}