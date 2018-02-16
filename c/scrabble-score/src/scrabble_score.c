#include "scrabble_score.h"
#include <stddef.h>
#include <ctype.h>

#define ALL 26

int score(const char *input)
{
	if ((input == NULL) || (*input == '\0'))
		return 0;

	const int scrabble[ALL] = {
	/*	A  B  C  D  E  F  G  H  I  J  K  L  M  */
		1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
		1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	/*	N, O  P  Q   R  S  T  U  V  W  X  Y  Z */

	int res = 0;
	int tmp;
	while (*input)
		if ((tmp = toupper(*input++) - 'A') >= 0
		    && tmp < ALL)
			res += scrabble[tmp];

	return res;
}
