#include "nucleotide_count.h"
#include <stdlib.h>
#include <stdio.h>

char *count(const char *dna_strand)
{
	char *error = (char*) malloc(1);
	*error = '\0';

	if (dna_strand == NULL)
		return error;

	int a, c, g, t;
	a = c = g = t = 0;
	char *tmp = (char*) dna_strand;
	while(*tmp)
		switch(*tmp++) {
		case 'A':
			a++;
			break;
		case 'C':
			c++;
			break;
		case 'G':
			g++;
			break;
		case 'T':
			t++;
			break;
		default:
			return error;
		}

	/* https://stackoverflow.com/a/3923207/6049386 */
	int size = snprintf(NULL, 0, "A:%i C:%i G:%i T:%i", a, c, g, t);

	char *res = (char*) malloc(size + 1);
	if (res == NULL)
		return error;

	sprintf(res, "A:%i C:%i G:%i T:%i", a, c, g, t);
	res[size] = '\0';

	free(error);
	return res;
}
