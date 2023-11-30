#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef _WIN32
#include <Windows.h>
#include <process.h>
#else
#include <stdio.h>
#include <pthread.h>
#endif

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
#endif

#ifdef _WIN32
static inline void threadCreate(void (*function)(void *), void *args)
{
    _beginthread(function, 0, args);
}
#else
static inline void threadCreate(void *(*function)(void *), void *args)
{
    pthread_create(&(pthread_t){0}, 0, function, args);
}
#endif

#endif /* __PLATFORM_H__ */
