#include "sieve.h"
#include <math.h>

/* https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes */
unsigned int sieve(const unsigned int limit, primes_array_t primes)
{
	if (!limit || !primes)
		return 0;

	int sieve[limit + 1];

	unsigned int i, j, upto;

	for (i = 2; i <= limit; i++)
		sieve[i] = 1;

	upto = (unsigned int) sqrt(limit);

	for (i = 2; i <= upto; i++)
		if (sieve[i] == 1)
			for (j = i*i; j <= limit; j += i)
				sieve[j] = 0;

	i = 0;
	for (j = 2; j <= limit; j++)
		if (sieve[j] == 1)
			primes[i++] = j;

	return i;
}
