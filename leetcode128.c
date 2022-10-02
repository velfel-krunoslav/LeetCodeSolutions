#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// Adapted from: https://www.journaldev.com/42955/radix-sort-algorithm

void radixSort(int arr[], int n)
{
    if (n <= 0)
    {
        return;
    }

    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
        else if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    int cycles = 0;

    while (min || max)
    {
        min /= 10;
        max /= 10;
        cycles++;
    }

    int newArray_[n];
    int *newArray = newArray_;

    for (int i = 0; i < cycles; i++)
    {
        int power = (int)pow(10, i);
        int count[19];

        memset(count, 0, sizeof(count));

        for (int j = 0; j < n; j++)
        {
            int num = ((arr[j] / power) % 10) + 9;
            count[num]++;
        }

        for (int j = 1; j < sizeof(count) / sizeof(count[0]); j++)
        {
            count[j] += count[j - 1];
        }

        for (int j = n - 1; j >= 0; j--)
        {
            unsigned int num = ((arr[j] / power) % 10) + 9;
            newArray[count[num] - 1] = arr[j];
            count[num]--;
        }
        int *t = arr;
        arr = newArray;
        newArray = t;
    }

    if (cycles % 2)
    {
        for (int i = 0; i < n; i++)
        {
            newArray[i] = arr[i];
        }
    }
}

int longestConsecutive(int *nums, int numsSize)
{
    if (!numsSize)
    {
        return 0;
    }
    radixSort(nums, numsSize);

    int max = 0;
    int count = 1;

    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] == nums[i - 1])
        {
            continue;
        }
        if ((nums[i] - 1) == nums[i - 1])
        {
            count++;
        }
        else
        {
            if (count > max)
            {
                max = count;
            }
            count = 1;
        }
    }
    if (count > max)
    {
        max = count;
    }

    return max;
}