#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node
{
    char *t;
    int count;
    struct node *next;
};

struct node *newNode(char *t)
{
    struct node *new = malloc(sizeof(struct node));
    new->t = t;
    new->next = NULL;
    new->count = 1;
    return new;
}

void addNode(char *t, struct node **head)
{

    if (*head == NULL)
    {
        *head = newNode(t);
    }
    else
    {
        struct node *u = *head, *uprev = NULL;
        struct node *new = newNode(t);

        new->next = *head;
        new->count += (*head)->count;
        *head = new;
    }
}

int getSignature(int *c, char *str)
{

    int slen = 0;
    memset(c, 0, 26 * sizeof(int));

    while (str[slen])
    {
        c[str[slen] - 'a']++;
        slen++;
    }

    return slen;
}

bool compareSignatures(int *f, int *s)
{

    int i = 0;
    while (i < 26)
    {
        if (f[i] != s[i])
        {
            return false;
        }
        i++;
    }

    return true;
}

char ***groupAnagrams(char **strs,
                      int strsSize,
                      int *returnSize,
                      int **returnColumnSizes)
{
    int **signatures = malloc(strsSize * sizeof(int *));

    int *signeeIdx = malloc(strsSize * sizeof(int));

    signatures[0] = malloc(26 * sizeof(int));
    getSignature(signatures[0], strs[0]);
    signeeIdx[0] = 0;

    int nsigns = 1;

    struct node **groupedStrs = calloc(strsSize, sizeof(struct node *));
    addNode(strs[0], groupedStrs);
    int *tmpSignature = malloc(26 * sizeof(int));

    for (int i = 1; i < strsSize; i++)
    {
        getSignature(tmpSignature, strs[i]);

        bool isDistinct = true;

        for (int j = 0; j < nsigns; j++)
        {
            if (compareSignatures(signatures[j], tmpSignature))
            {
                isDistinct = false;
                addNode(strs[i], groupedStrs + signeeIdx[j]);

                break;
            }
        }

        if (isDistinct)
        {
            signatures[nsigns] = tmpSignature;
            signeeIdx[nsigns] = i;
            nsigns++;
            tmpSignature = malloc(26 * sizeof(int));

            addNode(strs[i], groupedStrs + i);
        }
    }

    int groupsCount = 0;

    for (int i = 0; i < strsSize; i++)
    {
        if (groupedStrs[i] != NULL)
        {
            groupsCount++;
        }
    }

    *returnSize = groupsCount;
    *returnColumnSizes = malloc(groupsCount * sizeof(int));
    char ***groups = malloc(groupsCount * sizeof(char **));

    int q = 0;

    for (int i = 0; i < strsSize; i++)
    {
        if (groupedStrs[i] != NULL)
        {
            struct node *t = groupedStrs[i], *tprev = NULL;

            groups[q] = malloc(t->count * sizeof(char *));
            (*returnColumnSizes)[q] = t->count;

            for (int p = 0; t; tprev = t, t = t->next, p++)
            {
                groups[q][p] = t->t;

                if (tprev)
                {
                    free(tprev);
                }
            }

            if (tprev)
            {
                free(tprev);
            }

            q++;
        }
    }

    for (int i = 0; i < nsigns; i++)
    {
        free(signatures[i]);
    }
    free(signatures);
    free(groupedStrs);
    free(tmpSignature);
    free(signeeIdx);
    return groups;
}