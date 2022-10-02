#include <stdio.h>
#include <stdlib.h>

int mySqrt(int x)
{
    const double k = 0.00002;

    int i, y = x * k;
    for (i = y; (long)i * i <= (long)x; i++)
        ;
    i--;
    return i;
}