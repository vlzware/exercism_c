#include "gigasecond.h"
#include <stddef.h>
#include <stdbool.h>

#define GIGASEC 1000000000;

int get_year(int days)
{
	return days/365.2425;
}

time_t mktime(struct tm *date)
{
	if (date == NULL)
		return 0;
	return (time_t) (date->tm_year * date->tm_mon * date->tm_mday *
		date->tm_hour * date->tm_min * date->tm_sec);
}

time_t gigasecond_after(time_t before)
{
	time_t after = before + GIGASEC;
	return after;
}
