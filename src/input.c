#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "platform/thread.h"
#include "platform/getch.h"

ThreadR input(void *vargp)
{
    getchInit();
    int *out = ((InputArgs *)vargp)->out;
    bool *alive = ((InputArgs *)vargp)->alive;

    while (*alive)
    {
        *out = getch();
    }
    ThreadReturn;
}
