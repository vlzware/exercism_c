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
	/* check input */
	if (sentence == NULL || *sentence == '\0')
		return (char*) FINE;

	char *tmp = (char*) sentence;

	/* consume whitespace/silence */
	while (isspace(*tmp++))
		;
	if (*tmp == '\0')
		return (char*) FINE;

	/* try to start with an alpha */
	char q = 0;
	while (*tmp && !isalpha(*tmp)) {
		if (*tmp == '?')
			q = 1;
		tmp++;
	}
	/* no alpha in sentence */
	if (*tmp == '\0')
		return q ? (char*) SURE : (char*) WTEVER;

	/* parse the rest */
	int yelling = (isupper(*tmp++));
	while (*tmp) {
		if (isalpha(*tmp) && islower(*tmp))
			yelling = 0;
		/* yelling has precedence over question */
		if (*tmp == '?' && !yelling) {
			while (isspace(*++tmp))
				;
			if (*tmp == '\0')
				return (char*) SURE;
		} else {
			tmp++;
		}
	}

	if (yelling)
		return (char*) WHOA;

	return (char*) WTEVER;
}
