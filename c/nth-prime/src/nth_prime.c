#include "nth_prime.h"
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

uint32_t nth(const uint32_t n)
{
	if (!n)
		return 0;

	/* https://en.wikipedia.org/wiki/Prime_number_theorem\
		#Approximations_for_the_nth_prime_number */
	uint32_t limit =
		(uint32_t) (n * log(n) + n * log(log(n)));
	if (limit < 6)
		limit = 6;

	int *sieve = (int*) malloc(sizeof(int) * (limit + 1));
	if (sieve == NULL)
		return 0;

	uint32_t i, j, upto;

	for (i = 2; i <= limit; i++)
		sieve[i] = 1;

	upto = (uint32_t) sqrt(limit);

	for (i = 2; i <= upto; i++)
		if (sieve[i] == 1)
			for (j = i*i; j <= limit; j += i)
				sieve[j] = 0;

	i = 0;
	for (j = 2; j <= limit; j++)
		if (sieve[j] == 1)
			if (++i == n) {
				free(sieve);
				return j;
			}

	free(sieve);
	return 0;
}
