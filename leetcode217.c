#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct digit
{
    struct digit *next[10];
    unsigned short ends;
};

struct digit *newDigit()
{
    struct digit *new = malloc(sizeof(struct digit));

    memset(new->next, 0, 10 * sizeof(struct digit *));
    new->ends = (unsigned short)0U;

    return new;
}

bool insertNoDuplicates(int n, struct digit **head)
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

    bool alreadyInserted;

    if (tprev == NULL)
    {
        alreadyInserted = false;
    }
    else
    {
        alreadyInserted = (tprev->ends) & (0x1U << mprev);
        tprev->ends = tprev->ends | (0x1U << mprev);
    }

    return alreadyInserted;
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

bool containsDuplicate(int *nums, int numsSize)
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

        if (insertNoDuplicates(num, h) == true)
        {
            freeDigit(pos);
            freeDigit(neg);
            return true;
        }
    }

    freeDigit(pos);
    freeDigit(neg);
    return false;
}