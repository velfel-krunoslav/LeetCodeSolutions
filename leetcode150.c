#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef enum _operation
{
    DIV = 0,
    MUL = 1,
    ADD = 2,
    SUB = 3
} operation;

int _div(int a, int b)
{
    return a / b;
}
int _mul(int a, int b)
{
    return a * b;
}
int _add(int a, int b)
{
    return a + b;
}
int _sub(int a, int b)
{
    return a - b;
}

const int (*fns[4])(int, int) = {_div, _mul, _add, _sub};

int decode(char a)
{
    switch (a)
    {
    case '+':
        return ADD;
    case '-':
        return SUB;
    case '*':
        return MUL;
    case '/':
        return DIV;
    default:
        return -1;
    }
}

struct node
{
    int n;
    struct node *next;
};

void push(struct node **head, int n)
{
    struct node *new = malloc(sizeof(struct node));
    new->next = *head;
    new->n = n;
    *head = new;
}

void pop(struct node **head)
{
    if (*head == NULL)
    {
        return;
    }

    struct node *t = *head;
    *head = (*head)->next;
    free(t);
}

int evalRPN(char **tokens, int tokensSize)
{
    struct node *head = NULL;

    for (int i = 0; i < tokensSize; i++)
    {
        char *s = tokens[i];
        char *endptr = s + strlen(s);

        long t = strtol(tokens[i], &endptr, 10); // == atoi(tokens[i]);
        if (endptr == s)
        {
            int a = head->next->n, b = head->n;

            head->n = fns[decode(tokens[i][0])](a, b);
            pop(&(head->next));
        }
        else
        {
            push(&head, t);
        }
    }

    return head->n;
}