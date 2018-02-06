/**
 * Chech for anagrams:
 *
 * O(n) in the best case
 * O(log n) average
 * O(n^2) in the worst case
 *
 * i.e. one pass for each string + quicksort + strcmp
 *
 * A quicker solution is to use two vectors (arrays) of 26 (a-z)
 * but this would not work with unicode, or anything else than a-z
 */

#include "anagram.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* get length and convert to lowercase, copy w to ref */
int mstrlen_cp(char* w, char *ref)
{
	int res = 0;
	while (*w) {
		*w = tolower(*w);
		*ref++ = *w;
		res++;
		w++;
	}
	*ref = '\0';

	return res;
}

/* get length and convert to lowercase, compare to ref */
int mstrlen_ref(char* w, char *ref)
{
	int res = 0;
	int same = 0;
	while (*w) {
		*w = tolower(*w);
		if (ref && *ref && (*w == *ref)) {
			same++;
			ref++;
		}
		res++;
		w++;
	}
	if (res == same)
		return -1;

	return res;
}

/* qsort comparing function for char's */
int qsortcmp(const void *a, const void *b)
{
	const char *p = (const char *) a;
	const char *q = (const char *) b;

	return (*p - *q);
}

void anagrams_for(const char *word, struct candidates *candidates)
{
	if ((word == NULL) || (candidates == NULL))
		return;

	char or_word[MAX_STR_LEN];

	const int wlen = mstrlen_cp((char*) word, or_word);
	qsort((void *)word, wlen, 1, qsortcmp);

	int i;
	for (i = 0; i < (int)candidates->count; i++) {
		struct candidate *tmp = &(candidates->candidate[i]);
		int llen = mstrlen_ref((char*) tmp->candidate,
			   (char*) or_word);
		if (llen != wlen) {
			tmp->is_anagram = NOT_ANAGRAM;
		} else {
			qsort((void *)tmp->candidate, llen, 1, qsortcmp);
			int res = strcmp(word, tmp->candidate);
			tmp->is_anagram = res ? NOT_ANAGRAM : IS_ANAGRAM;
		}
	}
}
