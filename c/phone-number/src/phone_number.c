#include "phone_number.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *invalid = "0000000000";

int check_str(const char *s)
{
	if ((s == NULL) || (*s == '\0'))
		return -1;
	return strlen(s);
}

int is_allowed(char c)
{
	return (c == ' ' || c == '.' ||
		c == '-' || c == '(' || c == ')');
}

char *mcpy(char *dst, char *src)
{
	strcpy(dst, src);
	return dst;
}

char *phone_number_clean(const char *input)
{
	int len;
	if ((len = check_str(input)) < 0)
		return NULL;

	char *res = (char*) malloc(len + 1);
	if (res == NULL)
		return NULL;

	char *tmp_r = res;
	char *tmp_i = (char*) input;
	int digits = 0;
	while (*tmp_i) {
		if (isdigit(*tmp_i)) {
			*tmp_r = *tmp_i;
			tmp_r++;
			if (++digits > 11)
				return mcpy(res, (char*) invalid);
		} else if (!is_allowed(*tmp_i)) {
			return mcpy(res, (char*) invalid);
		}
		tmp_i++;
	}
	*tmp_r = '\0';

	if (digits < 10)
		return mcpy(res, (char*) invalid);

	if (digits == 11) {
	 	if (*input == '1')
			return mcpy(res, res + 1);
		else
			return mcpy(res, (char*) invalid);
	}

	return res;
}

char *phone_number_get_area_code(const char *input)
{
	int len;
	if ((len = check_str(input)) < 0)
		return NULL;

	return NULL;
}

char *phone_number_format(const char *input)
{
	int len;
	if ((len = check_str(input)) < 0)
		return NULL;

	return NULL;
}
