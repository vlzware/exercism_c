/* https://en.wikipedia.org/wiki/Wheat_and_chessboard_problem */

#include <math.h>
#include <stdint.h>
#define BOARD 64

uint64_t square(int which)
{
	if (which <= 0 || which > 64)
		return 0;

	return (uint64_t) pow(2, which - 1);
}

uint64_t total(void) {
	return (uint64_t) (pow(2, BOARD) - 1);
}
