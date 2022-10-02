#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define CMPTWO(x, y) (((x) > (y)) - ((x) < (y)))

int binarySearch(int *arr, int size, int x)
{
    int left = -1;
    int right = size;

    while (right > left + 1)
    {
        int middle = (left + right) / 2;
        if (arr[middle] >= x)
        {
            right = middle;
        }
        else
        {
            left = middle;
        }
    }

    if ((right < size) && (arr[right] == x))
    {
        return right;
    }
    return -1;
}

int compareTriplets(const int *f, const int *s)
{
    short p = CMPTWO(f[0], s[0]);
    short q = CMPTWO(f[1], s[1]);
    short r = CMPTWO(f[2], s[2]);

    return (p == 0) ? ((q == 0) ? ((r == 0) ? 0 : r) : q) : p;
}

int binarySearchTriplet(int **arr, int size, int *x, int *expectedIndex)
{
    int left = -1;
    int right = size;

    while (right > left + 1)
    {
        int middle = (left + right) / 2;
        if (compareTriplets(arr[middle], x) >= 0)
        {
            right = middle;
        }
        else
        {
            left = middle;
        }
    }

    if ((right < size) && (compareTriplets(arr[right], x) == 0))
    {
        return right;
    }
    else
    {
        *expectedIndex = right;
        return -1;
    }
}

int compare(const void *a, const void *b)
{
    return CMPTWO(*(int *)a, *(int *)b);
}

int **threeSum(int *a, int numsSize, int *returnSize, int **returnColumnSizes)
{
    qsort(a, numsSize, sizeof(int), compare);

    size_t sz = 2;

    int **result = malloc(sz * sizeof(int *));

    *returnColumnSizes = malloc(sz * sizeof(int *));
    (*returnColumnSizes)[0] = 0;
    *returnSize = 0;

    int tmp[3];

    int prev = INT_MIN, prevTwo;

    for (int i = 0; i < numsSize - 2; prev = a[i], i++)
    {
        prevTwo = !prev && !a[i];
        if ((prev == a[i]) || (prevTwo))
        {
            continue;
        }

        for (int j = i + 1; j < numsSize - 1; prev = a[j], j++)
        {
            prevTwo = !prev && !a[j];
            if ((prev == a[j]) || (prevTwo))
            {
                continue;
            }
            int target = a[i] + a[j];
            target *= -1;

            int t = -1;

            if (target >= a[j])
            {
                t = binarySearch(a + j + 1, numsSize - j - 1, target);
            }
            if (t != -1)
            {
                t += j + 1;
                tmp[0] = a[i];
                tmp[1] = a[j];
                tmp[2] = a[t];

                qsort(tmp, 3, sizeof(int), compare);

                int expectedIndex;

                int idx = binarySearchTriplet(result, *returnSize, tmp, &expectedIndex);

                if (idx == -1)
                {
                    if (sz == *returnSize)
                    {
                        sz *= 2;
                        result = realloc(result, sz * sizeof(int *));
                        *returnColumnSizes = realloc(*returnColumnSizes, sz * sizeof(int *));
                    }
                    result[*returnSize] = malloc(3 * sizeof(int));
                    memcpy(result[*returnSize], tmp, 3 * sizeof(int));
                    (*returnColumnSizes)[*returnSize] = 3;
                    (*returnSize)++;
                }
            }
        }
    }
    return result;
}