#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "platform/getch.h"

int input(void *vargp)
{
    int *out = ((InputArgs *)vargp)->out;
    bool *alive = ((InputArgs *)vargp)->alive;

    while (*alive)
    {
        *out = getch();
    }
    return 0;
}
