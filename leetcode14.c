#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *longestCommonPrefix(char **strs, int strsSize)
{
    int i, j;
    char *tmp;
    bool isTheSame;

    // Special edge case:
    if (strsSize == 1)
        return strdup(strs[0]);

    for (j = 0;; j++)
    {
        isTheSame = true;
        for (i = 1; i < strsSize && isTheSame; i++)
        {
            if (strs[i][j] == '\0' || strs[0][j] == '\0')
                goto finish;
            isTheSame = (strs[i][j] == strs[0][j]);
        }
        if (!isTheSame)
        {
            goto finish;
        }
    }

finish:
    tmp = strdup(strs[0]);
    tmp[j] = '\0';
    return tmp;
}