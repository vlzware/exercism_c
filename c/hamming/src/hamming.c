#include "hamming.h"
#include <string.h>

int compute(const char *dna_a, const char *dna_b)
{
	if (dna_a == NULL || dna_b == NULL)
		return -1;

	int diff = 0;
	while (*dna_a) {
		if (*dna_b == '\0')
			return -1;
		if (*dna_a++ != *dna_b++)
			diff++;
	}
	if (*dna_b)
		return -1;

	return diff;
}
