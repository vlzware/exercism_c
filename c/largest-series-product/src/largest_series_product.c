#include "largest_series_product.h"
#include <ctype.h>
#include <stddef.h>

int64_t largest_series_product(const char *input, const int series)
{
	if (series == 0)
		return 1;
	if ((input == NULL) || (series < 0) || (!isdigit(*input)))
		return -1;

	int i, len = 0;
	int64_t tmp, res = 0;
	while (*input) {
		for (i = 1, tmp = *input - '0'; (i < series) && *(input + i);
		     i++) {
			if (!isdigit(*(input + i)))
				return -1;
			tmp *= *(input + i) - '0';
		}
		if ((i == series) && (tmp > res))
			res = tmp;
		input++;
		len++;
	}
	if (len < series)
		return -1;

	return res;
}
