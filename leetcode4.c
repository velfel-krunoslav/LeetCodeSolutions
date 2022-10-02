#include <stdio.h>
#include <stdlib.h>

int findInSortedArray(int *arr, int size, int x)
{
    int left = -1;
    int right = size;

    while (right > left + 1)
    {
        int middle = (left + right) / 2;
        if (arr[middle] >= x)
            right = middle;
        else
            left = middle;
    }

    return right;
}

double calcMedian(int *arr, int sz)
{
    if (sz % 2 == 1)
        return (double)arr[sz / 2];
    else
        return (double)(arr[sz / 2] + arr[sz / 2 - 1]) / 2;
}

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    if (nums1Size == 0)
        return calcMedian(nums2, nums2Size);
    else if (nums2Size == 0)
        return calcMedian(nums1, nums1Size);

    int newSz = nums1Size + nums2Size;
    static int new[2000];

    int i1 = 0, i2 = 0, in = 0;
    while (in < newSz)
    {
        for (; i1 < nums1Size && (i2 >= nums2Size || nums1[i1] <= nums2[i2]); i1++)
        {
            new[in] = nums1[i1];
            in++;
        }
        for (; i2 < nums2Size && (i1 >= nums1Size || nums2[i2] <= nums1[i1]); i2++)
        {
            new[in] = nums2[i2];
            in++;
        }
    }

    double result = calcMedian(new, newSz);

    return result;
}