#include "sublist.h"

/* intint: search for subarray in array (brute force) */
static int intint(int *haystack, int *needle,
		  size_t haystack_len, size_t needle_len)
{
	size_t i, h, n;
	for (i = 0; i < haystack_len; i++) {
		for (h = i, n = 0; h < haystack_len && n < needle_len &&
		     (haystack[h] == needle[n]); h++, n++) ;
		if (n == needle_len)
			return i;
	}
	return -1;
}

comparison_result_t check_lists(int *list, int *base,
				size_t list_len, size_t base_len)
{
	if (list == NULL)
		return (base == NULL)
		    ? EQUAL : SUBLIST;
	if (base == NULL)
		return SUPERLIST;

	if ((list_len == base_len) &&
	    (intint(list, base, list_len, base_len) == 0))
		return EQUAL;

	else if ((list_len > base_len) &&
		 (intint(list, base, list_len, base_len) != -1))
		return SUPERLIST;

	/* list_len < base_len */
	else if (intint(base, list, base_len, list_len) != -1)
		return SUBLIST;

	return UNEQUAL;
}
