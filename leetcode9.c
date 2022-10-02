#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPalindrome(int x)
{
    char temp[12];

    sprintf(temp, "%d", x);

    int len = 0, i;

    for (len = 0; temp[len] != '\0'; len++)
        ;

    int lim = len / 2;

    for (i = 0; i < lim; i++)
    {
        if (temp[i] != temp[len - i - 1])
            return false;
    }

    return true;
}