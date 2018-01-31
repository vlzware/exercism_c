#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

#define ALL ('z' - 'a' + 1)

bool is_pangram(const char *sentence)
{
	if (sentence == NULL)
		return false;

	if (*sentence == '\0')
		return false;

	int lcount = 0;
	bool letters[ALL] = {false};

	int c;
	while (*sentence) {
		if (isalpha(*sentence)) {
			c = tolower(*sentence) - 'a';
			if (letters[c] == false) {
				if (++lcount == ALL)
					return true;
				letters[c] = true;
			}
		}
		sentence++;
	}

	return false;
}
