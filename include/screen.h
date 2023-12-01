#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <string.h>

typedef char Point;
typedef struct screen_t
{
    int width;
    int height;
    Point *screen;
} Screen;

Screen *screenCreate(int width, int height, Point fill_value);
void screenShow(Screen *screen);

static inline Point *screenGetPoint(Screen *screen, int x, int y)
{
    return screen->screen + x + (y * screen->width);
}

static inline void screenSet(Screen *screen, Point fill_value)
{
    memset(screen->screen, fill_value, screen->width * screen->height * sizeof(char));
}


#endif /* __SCREEN_H__ */
