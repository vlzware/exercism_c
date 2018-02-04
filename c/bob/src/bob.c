#include "bob.h"
#include <ctype.h>
#include <stddef.h>

#define SURE 	"Sure."
#define WHOA 	"Whoa, chill out!"
#define FINE 	"Fine. Be that way!"
#define WTEVER 	"Whatever."

/**
 * hey_bob: parsing sentence only once, searching for
 * question | yelling | silence | something
 */
char *hey_bob(const char *sentence)
{
	if (sentence == NULL)
		return (char*) FINE;

	char *tmp = (char*) sentence;
	int alphas = 0;
	int uppers = 0;
	char lastch = ' ';

	while (*tmp) {
		if (!isspace(*tmp)) {
			lastch = *tmp;
			if (isalpha(*tmp)) {
				alphas++;
				if (isupper(*tmp))
					uppers++;
			}
		}
		tmp++;
	}

	if (alphas && alphas == uppers)
		return (char*) WHOA;
	if (lastch == '?')
		return (char*) SURE;
	if (lastch == ' ')
		return (char*) FINE;

	return (char*) WTEVER;
}
