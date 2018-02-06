#ifndef ALLERGIES_H
#define ALLERGIES_H

#include <stdbool.h>

typedef enum {
   ALLERGEN_EGGS = 0,		/* 2^0 = 1 */
   ALLERGEN_PEANUTS,		/* 2^1 = 2 */
   ALLERGEN_SHELLFISH,		/* 2^2 = 4 */
   ALLERGEN_STRAWBERRIES,	/* ... */
   ALLERGEN_TOMATOES,
   ALLERGEN_CHOCOLATE,
   ALLERGEN_POLLEN,
   ALLERGEN_CATS,		/* 2^7 = 128 */
   ALLERGEN_COUNT
} allergen_t;

typedef struct {
   int count;
   allergen_t *allergens;
} allergen_list_t;

bool is_allergic_to(allergen_t allergen, int score);
void get_allergens(int score, allergen_list_t *list);

#endif
