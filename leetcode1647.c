#include <stdio.h>
#include <stdlib.h>

int minDeletions(char *s)
{
    int uniqueCount[26];
    int count[26];
    int uniqueLetters = 0;

    for (int i = 0; i < 26; i++)
        count[i] = 0;

    for (int i = 0; s[i]; i++)
        count[s[i] - 'a']++;

    for (int i = 0; i < sizeof(count) / sizeof(int); i++)
    {
        if (count[i])
        {
            int j;

            for (j = uniqueLetters; j > 0 && uniqueCount[j - 1] < count[i]; j--)
            {
                uniqueCount[j] = uniqueCount[j - 1];
            }

            uniqueCount[j] = count[i];

            uniqueLetters++;
        }
    }

    int result = 0;
    int i;

    for (i = 1; (i < uniqueLetters); i++)
    {
        if (uniqueCount[i] >= uniqueCount[i - 1])
        {
            int supposedVal = uniqueCount[i - 1] - 1;
            int actualVal = uniqueCount[i];
            if (supposedVal > 0)
            {
                result += actualVal - supposedVal;
                uniqueCount[i] = supposedVal;
            }
            else
            {
                result += uniqueCount[i];
                uniqueCount[i] = 0;
            }
        }
    }
    return result;
}