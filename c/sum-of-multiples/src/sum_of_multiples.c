#include "sum_of_multiples.h"
#include <stddef.h>

int alg_sum(int n)
{
	return n * (n + 1) / 2;
}

/* sum of multiples - mathematical approach */
int sum_of_multiples(const unsigned int *multiples, const int count,
		    const int n)
{
	if (multiples == NULL || count == 0)
		return 0;

	int i = 0, res = 0, multis = 1;
	for (; i < count; i++) {
		if (multiples[i] != 0) {
			res += multiples[i] * alg_sum((n - 1)/multiples[i]);
			multis *= multiples[i];
		}
	}
	if (count > 1)
		res -= multis * alg_sum((n - 1) / multis);
	return res;
}

#ifndef PROBLEM_TEST
#include <stdio.h>
int main (void)
{
	const unsigned int m[] = {4,6};
	printf("%i\n", sum_of_multiples(m, 2, 15));
	return 0;
}
#endif
