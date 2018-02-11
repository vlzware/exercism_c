#include "binary.h"
#include <string.h>

int convert(const char *binary)
{
	if (binary == NULL)
		return INVALID;

	int len = strlen(binary);
	if (len == 0)
		return INVALID;

	int res = 0;
	int i;

	for (i = 0; i < len; i++)
		if (binary[i] == '1')
			res |= 1 << (len - i - 1);
		else if (binary[i] != '0')
			return INVALID;

	return res;
}
