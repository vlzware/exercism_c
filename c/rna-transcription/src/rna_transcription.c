#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char* to_rna(const char* dna)
{
	if (dna == NULL)
		return NULL;

	char *res = (char*) malloc(strlen(dna) + 1);
	if (res == NULL)
		return NULL;

	char *tmp = res;
	while (*dna)
		switch(*dna++) {
		case 'G':
			*tmp++ = 'C';
			break;
		case 'C':
			*tmp++ = 'G';
			break;
		case 'T':
			*tmp++ = 'A';
			break;
		case 'A':
			*tmp++ = 'U';
			break;
		default:
			free(res);
			return NULL;
		}
	*tmp = '\0';

	return res;
}
