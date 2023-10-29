#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Screen *screenCreate(int width, int height, Point fill_value)
{
    Point *screen = malloc(width * height * sizeof(Point));
    memset(screen, fill_value, width * height * sizeof(Point));

    Screen *out = malloc(sizeof(Screen));
    out->width = width;
    out->height = height;
    out->screen = screen;
    return out;
}

void screenFree(Screen *screen)
{
    free(screen->screen);
    free(screen);
}

Point *screenGetPoint(Screen *screen, int x, int y)
{
    return screen->screen + x + (y * screen->width);
}

void screenShow(Screen *screen)
{
    int x, y, i;
    int width = screen->width;
    int height = screen->height;
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
