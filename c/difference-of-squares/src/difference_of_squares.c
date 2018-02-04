#include "difference_of_squares.h"

int square_of_sum(const int n)
{
	/* https://en.wikipedia.org/wiki/Triangular_number */
	int trnum = n * (n + 1) / 2;
	return (trnum * trnum);
}

int sum_of_squares(const int n)
{
	/* https://en.wikipedia.org/wiki/Square_pyramidal_number */
	return (n * (n + 1) * (2*n + 1) / 6);
}

int difference_of_squares(const int n)
{
	return (square_of_sum(n) - sum_of_squares(n));
}
