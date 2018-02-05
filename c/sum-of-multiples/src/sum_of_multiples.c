#include "sum_of_multiples.h"
#include <stddef.h>

#ifndef BRUTEFORCE
int alg_sum(int n)
{
	return (n * (n + 1))/2;
}
/* sum_of_multiples - mathematical approach */
/* would be usable if the elements are allowed to repeat */
int sum_of_multiples(const unsigned int *multiples, const int count,
		    const int n)
{
	if (multiples == NULL || count == 0)
		return 0;

	int i, res = 0;
	for (i = 0; i < count; i++) {
		if (multiples[i])
			res += multiples[i] * alg_sum((int) n/multiples[i]);
	}

	return res;
}
#endif

#ifdef BRUTEFORCE
/* sum_of_multiples - brute force approach */
int sum_of_multiples(const unsigned int *multiples, const int count,
		    const int n)
{
	if (multiples == NULL || count == 0)
		return 0;

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
#endif
