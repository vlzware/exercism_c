/* playing with ctime <--> mktime */

#include <stdio.h>
#include <time.h>

int main(void)
{
	struct tm info;

	info.tm_year = 1970 - 1900;
	info.tm_mon = 1 - 1;
	info.tm_mday = 1;
	info.tm_hour = 1;
	info.tm_min = 1;
	info.tm_sec = 1;
	info.tm_isdst = 0;

	time_t res = mktime(&info);
	printf("%s\n", ctime(&res));

	return 0;
}
