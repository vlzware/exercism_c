#include "sum_of_multiples.h"
#include <stddef.h>

int sum_of_multiples(const unsigned int *multiples, const int count,
		    const int n)
{
	if (multiples == NULL || count == 0 || !multiples[0])
		return 0;

	/* speedy solution */
	if (count == 1) {
		int tmp = (n - 1)/multiples[0];
		return multiples[0] * tmp * (tmp + 1) /2;

	}

	/* dumb brute force */
	int i, k, f, res = 0;
	for (i = 1; i < n; i++) {
		f = 0;
		for (k = 0; k < count; k++)
			if (!f && multiples[k] && !(i % multiples[k])) {
				res += i;
				f = 1;
			}
	}
	return res;
}
