#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum _brackets
{
    PARENTHESIS,
    SQUARE,
    CURLY
} brackets;

brackets decode(char a)
{
    if (a <= ')')
        return PARENTHESIS;
    if (a <= ']')
        return SQUARE;
    return CURLY;
}

int inc(char a)
{
    switch (decode(a))
    {
    case 0:
        return -((a + 1) % 3) + 1;
    case 1:
        return a - 92;
    default:
        return a - 124;
    }
}

struct node
{
    brackets b;
    struct node *next;
};

bool push(struct node **head, brackets b)
{
    struct node *new = malloc(sizeof(struct node));
    new->next = *head;
    new->b = b;
    *head = new;

    return true;
}

bool pop(struct node **head, brackets b)
{
    if (*head == NULL)
    {
        return false;
    }

    if((*head)->b != b)
    {
        return false;
    }

    struct node *t = *head;
    *head = (*head)->next;
    free(t);

    return true;
}

bool isValid(char *s)
{
    struct node *head = NULL;
    for (int i = 0; s[i]; i++)
    {
        int c = s[i];
        bool result;
        if(inc(c) < 0)
        {
            result = push(&head, decode(c));
        }
        else {
            result = pop(&head, decode(c));
        }

        if(!result)
        {
            return false;
        }
    }
    if(head)
    {
        return false;
    }
    return true;
}