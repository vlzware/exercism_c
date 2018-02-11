#include "collatz_conjecture.h"

int iseven(int n)
{
	return !(n & 1);
}

int steps(int start)
{
	if (start <= 0)
		return ERROR_VALUE;

	int res = 0;
	int n = start;
	while(n != 1) {
		n = (iseven(n))
			? n/2
			: 3*n + 1;
		res++;
	}
	return res;
}
