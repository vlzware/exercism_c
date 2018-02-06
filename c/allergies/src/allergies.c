#include "allergies.h"
#include <stdlib.h>
#include <stdio.h>

#define ALL 8 /* all allergens */

bool is_allergic_to(allergen_t allergen, int score)
{
	if (score < 0) {
		fprintf(stderr, "Invalid score\n");
		return false;
	}
	int a = 1 << allergen;
	return (score & a) == a;
}

void get_allergens(int score, allergen_list_t *list)
{
	if (score < 0) {
		fprintf(stderr, "Invalid score\n");
		return;
	}

	int all[ALL] = {0};

	/* get count */
	list->count = 0;
	int i, a;
	for (i = 0; i <= ALL - 1; i++) {
		a = 1 << i;
		if ((score & a) == a) {
			list->count++;
			all[i] = 1;
		}
	}

	/* alloc */
	list->allergens =
		(allergen_t *) malloc(list->count * sizeof(allergen_t));
	if (list->allergens == NULL) {
		fprintf(stderr, "Memory error\n");
		return;
	}

	/* fill */
	int k = 0;
	for (i = 0; i <= ALL - 1; i++)
		if (all[i])
			list->allergens[k++] = (allergen_t) i;
}
