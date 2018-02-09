#include "phone_number.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_str(const char *s);
char *err(char *res);
int is_allowed(char c);
void cpcnt(char **dst, char **src, int count);
void consume_space(char **s);
int peek(int count, int (*check) (int), char*s);

#define NUMLEN 10

char *phone_number_clean(const char *input)
{
	int len;
	if ((len = check_str(input)) < 0)
		return NULL;

	char *res = (char*) malloc(NUMLEN + 1);
	if (res == NULL)
		return NULL;

	char *tmp_r = res;
	char *tmp_i = (char*) input;
	int digits = 0;

	consume_space(&tmp_i);

	/* '+1 ' */
	if (*tmp_i == '+') {
		if (!(*(tmp_i + 1) == '1' && *(tmp_i + 2) == ' '))
			return err(res);
		tmp_i += 3;
		digits++;
	}

	/* '(ddd)' */
	if (*tmp_i == '(') {
		if (!peek(3, isdigit, tmp_i + 1) && *(tmp_i + 4) != ')')
			return err(res);
		tmp_i++;
		cpcnt(&tmp_r, &tmp_i, 3);
		tmp_i++;
		digits += 3;
	}

	consume_space(&tmp_i);

	if (*tmp_i == '1' && peek(NUMLEN, isdigit, tmp_i + 1))
		tmp_i++;

	while (*tmp_i) {
		if (isdigit(*tmp_i)) {
			if (++digits > NUMLEN)
				return err(res);
			*tmp_r = *tmp_i;
			tmp_r++;
		} else if (!is_allowed(*tmp_i)) {
			return err(res);
		}
		tmp_i++;
	}
	*tmp_r = '\0';

	if (digits != NUMLEN)
		return err(res);

	return res;
}

char *phone_number_get_area_code(const char *input)
{
	char *cl = phone_number_clean(input);
	char *res = (char*) malloc(4);
	if (res == NULL) {
		free(cl);
		return NULL;
	}

	res[0] = cl[0];
	res[1] = cl[1];
	res[2] = cl[2];
	res[3] = '\0';

	free(cl);

	return res;
}

char *phone_number_format(const char *input)
{
	char *cl = phone_number_clean(input);
	if (*cl == '0')
		return cl;

	char *res = (char*) malloc(15);
	if (res == NULL) {
		free(cl);
		return NULL;
	}

	int i;
	res[0] = '(';
	for (i = 0; i < 3; i++)
		res[1 + i] = cl[i];
	res[4] = ')';
	res[5] = ' ';
	for (i = 0; i < 3; i++)
		res[6 + i] = cl[3 + i];
	res[9] = '-';
	for (i = 0; i < 4; i++)
		res[10 + i] = cl[6 + i];
	res[14] = '\0';

	free(cl);
	return res;
}


/**
 ********************************************
 * helpers
 ********************************************
 */

int check_str(const char *s)
{
	if ((s == NULL) || (*s == '\0'))
		return -1;
	return strlen(s);
}

char *err(char *err)
{
	char *res = err;
	int i;
	for (i = 0; i < NUMLEN; i++)
		*err++ = '0';
	*err = '\0';
	return res;
}

int is_allowed(char c)
{
	return (c == ' ' || c == '.' || c == '-');
}

/* copy count chars skipping space */
void cpcnt(char **dst, char **src, int count)
{
	int i;
	for (i = 0; i < count; i++) {
		while (is_allowed(*(*src)))
			(*src)++;
		*(*dst)++ = *(*src)++;
	}
}

void consume_space(char **s)
{
	while (*(*s) == ' ')
		(*s)++;
}

int peek(int count, int (*check) (int), char*s)
{
	int i;
	for (i = 0; (i < count) && (*s); i++) {
		while(is_allowed(*s))
			s++;
		if (!check(*s++))
			return 0;
	}
	if (i < count)
		return 0;
	return 1;
}
