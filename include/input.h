#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdbool.h>

typedef struct input_args_t
{
    int *out;
    bool *alive;
} InputArgs;

#ifdef _WIN32
void input(void *vargp);
#else
void *input(void *vargp);
#endif

#endif /* __INPUT_H__ */
