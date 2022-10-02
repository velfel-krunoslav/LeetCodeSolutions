#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isAnagram(char *s, char *t)
{
    int c[26];
    int slen = 0, i;
    memset(c, 0, sizeof(c));

    while (s[slen])
    {
        c[s[slen] - 'a']++;
        slen++;
    }

    for (i = 0; t[i]; i++)
    {
        c[t[i] - 'a']--;

        if (c[t[i] - 'a'] < 0)
            return false;
    }
    if (slen != i)
        return false;
    return true;
}