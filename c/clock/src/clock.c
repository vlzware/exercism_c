#include "clock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clock(time_text_t time_text, int hour, int minute)
{
	if (time_text == NULL)
		return;

	int ch = 0, cm = 0;

	cm += minute % 60;
	if (cm < 0) {
		ch--;
		cm += 60;
	}

	ch += (hour + minute/60) % 24;
	if (ch < 0) {
		ch += 24;
	}

	sprintf(time_text, "%2.2i:%2.2i", ch, cm);
}

void clock_add(time_text_t time_text, int minute_offset)
{
	if (time_text == NULL)
		return;

	char buf[3] = {0};

	strncpy(buf, time_text, 2);
	int hour = atoi(buf);

	strncpy(buf, (time_text + 3), 2);
	int minute = atoi(buf);

	clock(time_text, hour, minute + minute_offset);
}
