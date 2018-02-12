#include "palindrome_products.h"
#include <stdio.h>

int palindrome(int n);
void addfactors(product_t p, int i, int k);

product_t get_palindrome_product(unsigned int from, unsigned int to)
{
	if (from > to) {
		from ^= to;
		to ^= from;
		from ^= to;
	}

	product_t res;
	res.smallest = from*to;
	res.largest = from;
	res.factors_lg = NULL;
	res.factors_sm = NULL;

	unsigned int i, k, n;
	for (i = from; i <= to; i++)
		for (k = i; k <= to; k++)
			if (palindrome(n = i*k)) {
				if (n <= res.smallest) {
					res.smallest = n;
					addfactors(res, i, k);
				} else if (n >= res.largest) {
					res.largest = n;
					addfactors(res, i, k);
				}
			}

	return res;
}

int palindrome(int n)
{
	if (n < 0)
		return 0;

	int r = 0;
	int nn = n;

	/* inverse n in r */
	while (n >= 1) {
		r = (r * 10) + (n % 10);
		n /= 10;
	}

	return (nn == r);
}

void addfactors(product_t p, int i, int k)
{
	p = p; i = i; k = k;
}
