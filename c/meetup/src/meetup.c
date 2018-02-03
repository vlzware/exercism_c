#include "meetup.h"
#include <string.h>

const char* days[] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

#define MAXWEEKS 6
#define MAXDAYS 7
int curr_month[MAXWEEKS][MAXDAYS];

int is_leap(const int year);
int get_week_day_num(const char* day);
int get_week_day(const int day, const int month, int year);
int get_first_day(const int year, const int month);
void construct_month(const int year, const int month);
int parse_modif(const char *modif);

/*
	Accepted modifiers:
	"first", "second", "third", "fourth", "fifth",
	"last" and "teenth" (meaning 13 <= "teenth" <= 19)

	month is 1..12
*/
int meetup_day_of_month(const int year, const int month, const char *modif,
		const char *day)
{
	if ((month < 1) || (month > 12))
		return 0;

	int day_num = get_week_day_num(day);
	if (day_num == -1)
		return 0;

	construct_month(year, month);

	int i;
	if (strcmp("teenth", modif) == 0) {
		for (i = 0; i < MAXWEEKS; i++)
			if (curr_month[i][day_num] > 12)
				return curr_month[i][day_num];
		return 0;
	}

	if (strcmp("last", modif) == 0) {
		for (i = MAXWEEKS -1; i >= 0; i--)
			if (curr_month[i][day_num] > 0)
				return curr_month[i][day_num];
		return 0;
	}

	int count = 0;
	int target = parse_modif(modif);

	for (i = 0; i < MAXWEEKS; i++) {
		if (curr_month[i][day_num] > 0)
			if (++count == target)
				return curr_month[i][day_num];
	}
	return 0;
}

int is_leap(const int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int get_week_day_num(const char* day)
{
	int i;
	for (i = 0; i < 7; i++) {
		if (strcmp(days[i], day) == 0)
		return i;
	}
	return -1;
}

/* http://blog.hackerearth.com/2016/11/\
	algorithm-on-how-to-find-the-day-of-week.html */
int get_week_day(const int day, const int month, int year)
{
	int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	year -= month < 3;
	return (year + (int)(year/4) - (int)(year/100) + (int)(year/400) +
		t[month-1] + day) % 7;
}

int get_first_day(const int year, const int month)
{
	return get_week_day(1, month, year);
}

void construct_month(const int year, const int month)
{
	memset(curr_month, 0, sizeof(curr_month));
	int months[12] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	if (is_leap(year))
		months[1] = 29;

	int week_day = get_first_day(year, month);
	int week = 0;
	int date;

	for (date = 1; date <= months[month -1]; date++) {
		curr_month[week][week_day] = date;
		if (++week_day == MAXDAYS) {
			week_day = 0;
			week++;
		}
	}
}

int parse_modif(const char *modif)
{
	return	(strcmp("first", modif)  == 0) ? 1 :
		(strcmp("second", modif) == 0) ? 2 :
		(strcmp("third", modif)  == 0) ? 3 :
		(strcmp("fourth", modif) == 0) ? 4 :
		(strcmp("fifth", modif)  == 0) ? 5 : -1;
}
