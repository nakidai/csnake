#include "screen.h"

int main(int argc, char **argv)
{
    Screen *screen = screenCreate(5, 5, '#');
    screenShow(screen);
    return 0;
}
