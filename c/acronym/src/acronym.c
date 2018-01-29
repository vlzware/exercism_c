#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

char *abbreviate(const char *phrase)
{
	char *res = NULL;
	int len = 0;

	if (!phrase)
		return NULL;

	len = strlen(phrase);
	if (!len)
		return NULL;

	res = malloc(len + 1);
	if (!res) {
		fprintf(stderr, "Memory error!\n");
		return NULL;
	}

	char *tmp = res;
	bool wordstart = true;

	while(*phrase) {
		if (isalpha(*phrase)) {
			if (wordstart) {
				wordstart = false;
				*tmp++ = toupper(*phrase);
			}
		} else {
			wordstart = true;
		}
		phrase++;
	}
	*tmp = '\0';

	return res;
}