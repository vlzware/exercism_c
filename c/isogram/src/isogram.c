#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define CCOUNT ('z' - 'a' + 1)

bool is_isogram(const char phrase[])
{
    bool letters[CCOUNT] = {false};

    int p_len = strlen(phrase);
    int i, c, k;

    for (i = 0; i < p_len; i++) {
        c = tolower(phrase[i]);

        if (c == ' ' || c == '-')
            continue;

        if (!isalpha(c))
            return false;

        k = c - 'a';
        if (letters[k])
            return false;

        letters[k] = true;
    }
    return true;
}