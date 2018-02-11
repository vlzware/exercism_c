#include "perfect_numbers.h"
#include <math.h>

int aliquot(int n)
{
	if (n < 4)
		return 0;

	int res = 0;
	int i;
	int up = sqrt(n);
	for (i = 2; i <= up; i++)
		if (n % i == 0)
			res += (i == n/i)? i : (i + n/i);

	return res + 1;
}

kind classify_number(int n)
{
	if (n <= 0)
		return ERROR;

	int aq = aliquot(n);

	if (aq == n)
		return PERFECT_NUMBER;
	if (aq > n)
		return ABUNDANT_NUMBER;
	return DEFICIENT_NUMBER;
}
