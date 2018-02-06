#include "atbash_cipher.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAGIC 219

void addspace(char **tmp, int *count)
{
	if (*count == 5) {
		*count = 0;
		*(*tmp)++ = ' ';
	}
}

/* modes: 0 = decode; 1 = encode */
char *parse(char *input, int mode)
{
	int len = strlen(input);
	char *tmp = (char*) malloc(len + mode * len/5 + 1);
	if (tmp == NULL)
		return NULL;

	char *res = tmp;
	int count = 0;
	while (*input) {
		if (isalpha(*input)) {
			addspace(&tmp, &count);
			*tmp = MAGIC - tolower(*input);
			count += mode;
			tmp++;
		} else if (isdigit(*input)) {
			addspace(&tmp, &count);
			*tmp = *input;
			count += mode;
			tmp++;
		}
		input++;
	}
	*tmp = '\0';
	return res;
}

char *atbash_encode(char *input)
{
	return parse(input, 1);
}

char *atbash_decode(char *input)
{
	return parse(input, 0);
}
