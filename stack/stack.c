#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
OBJ *push(OBJ *top, double data)
{
    OBJ *ptr = malloc(sizeof(OBJ));
    ptr->data = data;
    ptr->next = top;

    return ptr;
}

OBJ *pop(OBJ *top)
{
    if (top == NULL)
    {
        return top;
    }
    OBJ *next_ptr = top->next;
    free(top);

    return next_ptr;
}

void free_stack(OBJ *top)
{
    while (top != NULL)
    {
        top = pop(top);
    }
}