#ifndef FORMATS__H
#define FORMATS__H

#define FMT_DAY_MO_YR "DDMMAAAA" 
#define FMT_YR_DAY "AAAADDD" /*Día (sobre los 365) del año.*/
#define FMT_YR_MO_DAY "AAAAMMDD"
#define FMT_YR_MO_DAY_HR_MIN_SEC "AAAAMMDDHHmmSS" /*El día del mes.*/
#define FMT_YR_DAY_HR_MIN_SEC "AAAADDDHHmmSS" /*El día del año.*/

status_t print_as_day_month_year(struct tm * time);
status_t sysdate(char * format);

#endif