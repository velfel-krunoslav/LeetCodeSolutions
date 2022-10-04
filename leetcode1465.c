void radixSort(int **arr_, int size)
{
    int t = 0;

    int digits[10];

    int *arr = *arr_;
    int *idx = malloc(sizeof(int) * size);

    memcpy(idx, arr, sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        int j;
        int q = idx[i];
        for (j = 0; q; j++, q /= 10)
            ;
        if (j > t)
        {
            t = j;
        }
    }

    long factor = 1;

    for (int i = 0; i <= t; i++, factor *= 10)
    {
        memset(digits, 0, 10 * sizeof(int));

        for (int j = 0; j < size; j++)
        {
            digits[((long)arr[j] / factor) % 10]++;
        }

        for (int j = 1; j < 10; j++)
        {
            digits[j] += digits[j - 1];
        }

        for (int j = size - 1; j >= 0; j--)
        {
            int c = ((long)arr[j] / factor) % 10;
            int v = --digits[c];
            idx[v] = arr[j];
        }

        int *w = idx;
        idx = arr;
        arr = w;
    }

    if (t % 2 == 0)
    {
        int *w = idx;
        idx = arr;
        arr = w;
    }

    free(*arr_);
    *arr_ = idx;
}

int widestGap(int *arr, int arrSize, int wh)
{
    radixSort(&arr, arrSize);

    int maxGap = arr[0];
    for (int i = 1; i < arrSize; i++)
    {
        int t = arr[i] - arr[i - 1];
        if (t > maxGap)
        {
            maxGap = t;
        }
    }

    int t = wh - arr[arrSize - 1];
    if (t > maxGap)
    {
        maxGap = t;
    }

    free(arr);
    return maxGap;
}

int maxArea(int h,
            int w,
            int *horizontalCuts,
            int horizontalCutsSize,
            int *verticalCuts,
            int verticalCutsSize)
{
    int p = widestGap(horizontalCuts, horizontalCutsSize, h);
    int q = widestGap(verticalCuts, verticalCutsSize, w);

    return (int)((long)p * q % 1000000007);
}
