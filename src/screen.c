#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

void screenCreate(Screen *buffer, int width, int height, Point fill_value)
{
    Point *screen = malloc(width * height * sizeof(Point));
    memset(screen, fill_value, width * height * sizeof(Point));

    buffer->width = width;
    buffer->height = height;
    buffer->screen = screen;
}

void screenShow(Screen screen)
{
    int x, y, i;
    int width = screen.width;
    int height = screen.height;
    Point point;

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            point = *screenGetPoint(screen, x, y);
            for (i = 0; i < 2; ++i) putchar(point);
        }
        putchar('\n');
    }
}
