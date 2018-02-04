#include "raindrops.h"
#include <stdio.h>

void mcat(int *pos, const char *dst, const char *src_);
int check_mod(int a, int b);

void convert(char *buf, int drops)
{
	int found = 0;
	int pos = 0;
	if (check_mod(drops, 3)) {
		mcat(&pos, buf, "Pling");
		found = 1;
	}
	if (check_mod(drops, 5)) {
		mcat(&pos, buf, "Plang");
		found = 1;
	}
	if (check_mod(drops, 7)) {
		mcat(&pos, buf, "Plong");
		found = 1;
	}

	if (!found)
		sprintf(buf, "%i", drops);
}

/**
 * mcat: concatenate strings, puts the new length in pos,
 * assumes dst is big enough
 */
void mcat(int *pos, const char *dst, const char *src_)
{
	char *src = (char*) src_;
	char *tmp = (char*) dst + *pos;
	while ((*tmp++ = *src++))
		(*pos)++;
	*tmp = '\0';
}

int check_mod(int a, int b)
{
	return (a % b == 0);
}
