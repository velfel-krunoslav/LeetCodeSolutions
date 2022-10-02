#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct height
{
    //  d[n, i];
    int d[2];
};

// Adapted from: https://www.journaldev.com/42955/radix-sort-algorithm

void radixSort(struct height arr[], int n, int offset, int cycles)
{
    struct height newArray_[n];
    struct height *newArray = newArray_;

    for (int i = 0; i < cycles; i++)
    {
        int power = (int)pow(10, i);
        int count[10];

        memset(count, 0, sizeof(count));

        for (int j = 0; j < n; j++)
        {
            int num = 9 - ((arr[j].d[offset] / power) % 10);
            count[num]++;
        }

        for (int j = 1; j < 10; j++)
        {
            count[j] += count[j - 1];
        }

        for (int j = n - 1; j >= 0; j--)
        {
            unsigned int num = 9 - ((arr[j].d[offset] / power) % 10);
            newArray[count[num] - 1] = arr[j];
            count[num]--;
        }
        struct height *t = arr;
        arr = newArray;
        newArray = t;
    }

    if (cycles % 2)
    {
        for (int i = 0; i < n; i++)
        {
            arr[i] = newArray[i];
        }
    }
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int maxArea(int *height, int heightSize)
{
    struct height h[heightSize];
    for (int i = 0; i < heightSize; i++)
    {
        h[i] = (struct height){.d = {height[i], i}};
    }

    radixSort(h, heightSize, 0, 6);

    int copyIndex = 0;
    int repetitions = 0;

    int i = 0;

    do
    {
        h[copyIndex] = h[i];
        copyIndex++;
        if ((i < heightSize - 1) && (h[i].d[0] == h[i + 1].d[0]))
        {
            int k;
            for (k = i; (k < heightSize) && (h[i].d[0] == h[k].d[0]); k++)
                ;
            k--;
            i = k;
        }
        else
        {
            i++;
        }
    } while (i < heightSize);

    heightSize = copyIndex;

    int leftmost = h[0].d[1];
    int rightmost = h[1].d[1];

    /* The first element may not have any repetitions.
     * Therefore, the indices may not be in the correct order
     * and an additional check needs to be performed:
     */

    if (rightmost < leftmost)
    {
        swap(&leftmost, &rightmost);
    }

    int max = h[1].d[0] * (rightmost - leftmost);

    for (int i = 2; i < heightSize; i++)
    {
        int t = h[i].d[1];
        if (t < leftmost)
        {
            swap(&t, &leftmost);
        }
        if (t > rightmost)
        {
            swap(&t, &rightmost);
        }

        t = h[i].d[0] * (rightmost - leftmost);

        if (t > max)
        {
            max = t;
        }
    }
    return max;
}