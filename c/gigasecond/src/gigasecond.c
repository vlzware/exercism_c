#include "gigasecond.h"
#include <stddef.h>
#include <stdbool.h>

#define GIGASEC 1000000000;

int get_year(int days)
{
	return days/365.2425;
}

time_t gigasecond_after(time_t before)
{
	time_t after = before + GIGASEC;
	return after;
}
