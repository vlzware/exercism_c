#include "allergies.h"
#include <stdlib.h>
#include <stdio.h>

bool is_allergic_to(allergen_t allergen, int score)
{
	if (score < 0) {
		fprintf(stderr, "Invalid score\n");
		return false;
	}
	return (score & (1 << allergen));
}

void get_allergens(int score, allergen_list_t *list)
{
	if (score < 0) {
		fprintf(stderr, "Invalid score\n");
		return;
	}

	list->allergens =
		(allergen_t *) malloc(list->count * sizeof(allergen_t));
	if (list->allergens == NULL) {
		fprintf(stderr, "Memory error\n");
		return;
	}

	list->count = 0;
	int i;
	for (i = 0; i <= ALLERGEN_COUNT - 1; i++) {
		if ((score & (1 << i))) {
			list->allergens[list->count++] = (allergen_t) i;
		}
	}
}
