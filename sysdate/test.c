#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t raw_time;
	struct tm * cal_ptr;
	if ((raw_time = time(NULL)) == -1)
		return 1;
	if((cal_ptr = localtime(&raw_time)) == NULL)
		return 1;
	printf("Día del año: %02d Día del mes:%02d %02d:%02d:%02d\n",cal_ptr -> tm_yday, cal_ptr->tm_mday, cal_ptr->tm_hour, cal_ptr->tm_min, cal_ptr->tm_sec);
	return 0;
}
