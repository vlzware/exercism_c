#ifndef PALINDROME_PRODUCTS_H
#define PALINDROME_PRODUCTS_H

struct factors {
	unsigned int factor_a;
	unsigned int factor_b;
	struct factors *next;
};

struct product {
	unsigned int smallest;
	unsigned int largest;
	struct factors *factors_sm;
	struct factors *factors_lg;
};

typedef struct product product_t;

product_t get_palindrome_product(unsigned int from, unsigned int to);

#endif
