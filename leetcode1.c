#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct num
{
    int n;
    int i;
};

void radixSort(struct num arr[], int n, int cycles)
{
    struct num newArray_[n];
    struct num *newArray = newArray_;

    int count[19];
    int power = 1;
    for (int i = 0; i < cycles; i++)
    {
        memset(count, 0, 19 * sizeof(int));

        for (int j = 0; j < n; j++)
        {
            int num = ((arr[j].n / power) % 10) + 9;
            count[num]++;
        }

        for (int j = 1; j < 19; j++)
        {
            count[j] += count[j - 1];
        }

        for (int j = n - 1; j >= 0; j--)
        {
            unsigned int num = ((arr[j].n / power) % 10) + 9;
            newArray[count[num] - 1] = arr[j];
            count[num]--;
        }
        struct num *t = arr;
        arr = newArray;
        newArray = t;

        power *= 10;
    }

    if (cycles % 2)
    {
        for (int i = 0; i < n; i++)
        {
            newArray[i] = arr[i];
        }
    }
}

int binarySearch(struct num *arr, int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid].n == x)
            return mid;

        if (arr[mid].n > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    struct num *a = malloc(numsSize * sizeof(struct num));
    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] < min)
        {
            min = nums[i];
        }
        if (nums[i] > max)
        {
            max = nums[i];
        }
        a[i].n = nums[i];
        a[i].i = i;
    }

    int cycles = 0;

    while (min != 0 || max != 0)
    {
        min /= 10;
        max /= 10;
        cycles++;
    }

    int *res = malloc(2 * sizeof(int));
    *returnSize = 2;

    radixSort(a, numsSize, cycles);

    for (int i = 0; i < numsSize; i++)
    {
        if ((target > a[i].n) || (target - a[i].n > a[i].n))
        {
            if (i + 2 <= numsSize)
            {
                int j = binarySearch(a + i + 1, 0, numsSize - i - 2, target - a[i].n);
                if (j >= 0)
                {
                    res[0] = a[i].i;
                    res[1] = a[j + i + 1].i;
                    goto finish;
                }
            }
        }
        else
        {
            if (i >= 1)
            {
                int j = binarySearch(a, 0, i, target - a[i].n);
                if (j >= 0)
                {
                    res[0] = a[i].i;
                    res[1] = a[j].i;
                    goto finish;
                }
            }
        }
    }

finish:
    free(a);
    return res;
}