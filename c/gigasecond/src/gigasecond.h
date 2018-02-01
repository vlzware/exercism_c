#ifndef GIGASECOND_H
#define GIGASECOND_H

#include <stdint.h>

typedef uint32_t time_t;

struct tm {
	int tm_year;
	int tm_mon;
	int tm_mday;
	int tm_hour;
	int tm_min;
	int tm_sec;
	int tm_isdst;
};

time_t mktime(struct tm *date);
time_t gigasecond_after(time_t now);

#endif
