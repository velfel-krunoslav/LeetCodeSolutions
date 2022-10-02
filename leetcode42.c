#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int _trap(int *height, int heightSize)
{
    // Recursion exit condition:
    if (heightSize <= 1)
        return 0;

    int maxIndex = -1, prevMaxIndex = -1;
    int maxVal = -1, prevMaxVal = -1;

    for (int i = 0; i < heightSize; i++)
    {
        if (height[i] > maxVal)
        {
            prevMaxIndex = maxIndex;
            prevMaxVal = prevMaxVal;
            maxIndex = i;
            maxVal = height[maxIndex];
        }
        else if (height[i] > prevMaxVal)
        {
            prevMaxIndex = i;
            prevMaxVal = height[prevMaxIndex];
        }
    }

    int result = 0;

    int lbv, ubv;
    int lowerBound, upperBound;

    if (prevMaxIndex < maxIndex)
    {
        lowerBound = prevMaxIndex;
        upperBound = maxIndex;
    }
    else
    {
        lowerBound = maxIndex;
        upperBound = prevMaxIndex;
    }

    if (height[prevMaxIndex] < height[maxIndex])
    {
        lbv = height[prevMaxIndex];
        ubv = height[maxIndex];
    }
    else
    {
        lbv = height[maxIndex];
        ubv = height[prevMaxIndex];
    }

    int t = upperBound - lowerBound;

    t = (t - 1) * lbv;

    for (int i = lowerBound + 1; i < upperBound; i++)
    {
        t -= height[i];
    }

    result += t;

    result += _trap(height, lowerBound + 1);
    result += _trap(height + upperBound, heightSize - upperBound);

    return result;
}

int trap(int *height, int heightSize)
{
    // Trim unnecessary elements from the left and the right
    int q;
    for (q = 0; q < heightSize - 1; q++)
    {
        if (height[q + 1] < height[q])
            break;
    }
    height = height + q;
    heightSize -= q;

    for (q = heightSize - 1; q >= 1; q--)
    {
        if (height[q - 1] < height[q])
            break;
    }
    q++;
    heightSize = q;

    return _trap(height, heightSize);
}