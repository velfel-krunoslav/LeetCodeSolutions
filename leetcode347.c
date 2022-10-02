#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

struct digit
{
    struct digit *next[10];
    int ends[10];
};

struct count
{
    int num;
    int count;
};

struct digit *newDigit()
{
    struct digit *new = malloc(sizeof(struct digit));

    memset(new->next, 0, 10 * sizeof(struct digit *));
    memset(new->ends, 0, 10 * sizeof(int));

    return new;
}

int insertAndCountOccurences(int n, struct digit **head)
{
    if (head == NULL)
    {
        return false;
    }

    struct digit *t, *tprev;
    int m, mprev;

    m = n;
    t = *head;
    tprev = NULL;

    do
    {
        if (t == NULL)
        {
            if (tprev == NULL)
            {
                *head = t = newDigit();
            }
            else
            {
                tprev->next[mprev % 10] = t = newDigit();
            }
        }
        tprev = t;
        t = t->next[m % 10];

        mprev = m;
        m /= 10;
    } while (m);

    if (n == 0)
    {
        tprev = *head;
        mprev = 0;
    }
    if (tprev == NULL)
    {
        return 1;
    }
    else
    {
        return ++(tprev->ends[mprev]);
    }
}

void freeDigit(struct digit *node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < 10; i++)
    {
        freeDigit(node->next[i]);
    }
    free(node);
}

void listAllNums(struct digit *node, bool positive, int prevVal, int depth)
{
    if (node == NULL)
        return;

    for (int i = 0; i < 10; i++)
    {
        if (node->ends[i])
        {
            printf("%d\n", ((positive) ? 1 : -1) * ((int)pow(10, depth) * i + prevVal));
        }

        listAllNums(node->next[i], positive, ((int)pow(10, depth) * i + prevVal), depth + 1);
    }
}

void countOccurences(struct digit *node,
                     bool positive,
                     int prevVal,
                     struct count *occurences,
                     int *size,
                     int depth)
{
    if (node == NULL)
        return;

    for (int i = 0; i < 10; i++)
    {

        if (node->ends[i])
        {
            occurences[*size].count = node->ends[i];
            occurences[*size].num = ((positive) ? 1 : -1) * ((int)pow(10, depth) * i + prevVal);
            (*size)++;
        }

        countOccurences(node->next[i],
                        positive,
                        ((int)pow(10, depth) * i + prevVal),
                        occurences,
                        size,
                        depth + 1);
    }
}

int compare(const void *a, const void *b)
{
    return ((struct count *)a)->count - ((struct count *)b)->count;
}

int *topKFrequent(int *nums, int numsSize, int k, int *returnSize)
{
    struct digit *pos = NULL, *neg = NULL;

    for (int i = 0; i < numsSize; i++)
    {
        struct digit **h;
        int num = nums[i];
        if (num >= 0)
        {
            h = &pos;
        }
        else
        {
            num *= -1;
            h = &neg;
        }

        insertAndCountOccurences(num, h);
    }
    struct count *occurences = malloc(numsSize * sizeof(struct count));

    *returnSize = k;
    int *maxNums = malloc(k * sizeof(int));

    int p = 0;

    countOccurences(pos, true, 0, occurences, &p, 0);
    countOccurences(neg, false, 0, occurences, &p, 0);

    qsort(occurences, p, sizeof(struct count), compare);

    for (int i = 0; i < k; i++)
    {
        maxNums[i] = occurences[p - i - 1].num;
    }

    freeDigit(pos);
    freeDigit(neg);
    free(occurences);

    return maxNums;
}