#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdbool.h>

typedef struct input_args_t
{
    int *out;
    bool *alive;
} InputArgs;

int input(void *vargp);

#endif /* __INPUT_H__ */
