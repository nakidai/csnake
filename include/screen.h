#ifndef __SCREEN_H__
#define __SCREEN_H__

typedef struct screen_t
{
    int width;
    int height;
    char *screen;
} Screen;
typedef char Point;

Screen *screenCreate(int width, int height, Point fill_value);
void screenFree(Screen *screen);

Point *screenGetPoint(Screen *screen, int x, int y);
void screenShow(Screen *screen);
void screenSet(Screen *screen, char fill_value);

#endif /* __SCREEN_H__ */
