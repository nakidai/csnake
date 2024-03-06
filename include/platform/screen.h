#ifndef __PLATFORM_SCREEN_H__
#define __PLATFORM_SCREEN_H__

#ifdef _WIN32
#include <windows.h>
#else
#include <stdio.h>
#endif /* _WIN32 */

#ifdef _WIN32
static inline void resetCoordinates(void)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, (COORD){0});
}
#else
static inline void resetCoordinates(void)
{
    printf("\e[1;1H\e[2J");
}
#endif /* _WIN32 */

#endif /* __PLATFORM_SCREEN_H__ */
