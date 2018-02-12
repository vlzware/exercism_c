#include "all_your_base.h"
#include <math.h>
#include <stdio.h>

#define TESTS_CONDITIONS

void zeros(int8_t digits[], int start, int len);
int todec(int8_t digits[], int16_t input_base, size_t input_length,
	   int start);
size_t convert(int8_t digits[], int16_t output_base, int dec);


size_t rebase(int8_t digits[], int16_t input_base, int16_t output_base,
	      size_t input_length)
{
	/* input check */
	if (
		digits == NULL || input_base <= 1 ||
		output_base <= 1 || input_length <= 0 ||
		input_length >= DIGITS_ARRAY_SIZE
	)
		return 0;


	/* consume leading zeros - how I think it should be */
	int start = 0;
	while (digits[start] == 0)
		start++;

	/* check for leading zeros - as per the tests */
	#ifdef TESTS_CONDITIONS
	if (digits[0] == 0)
		return 0;
	#endif

	/* convert do tecimal */
	int dec = todec(digits, input_base, input_length, start);

	/* convert to output_base */
	size_t res = convert(digits, output_base, dec);
	if (dec == 0)
		return 0;

	/* zero the rest of digits */
	zeros(digits, res, DIGITS_ARRAY_SIZE);

	return res;
}


void zeros(int8_t digits[], int start, int len)
{
	int i;
	for (i = start; i < len; i++)
		digits[i] = 0;
}

int todec(int8_t digits[], int16_t input_base, size_t input_length,
	   int start)
{
	int i, dec = 0;
	for (i = start; i < (int) input_length; i++) {
		if (digits[i] < 0 || digits[i] >= input_base)
			return 0;
		dec += pow(input_base, (input_length - i - 1)) * digits[i];
	}
	return dec;
}

size_t convert(int8_t digits[], int16_t output_base, int dec)
{
	size_t res = 0;

	/* count length of output */
	int q = dec;
	while (q) {
		q /= output_base;
		res++;
	}
	if (!(res < DIGITS_ARRAY_SIZE))
		return 0;

	/* build the output counting for endianness */
	int len = res;
	while (dec) {
		len--;
		digits[len] = dec % output_base;
		dec /= output_base;
	}
	return res;
}
