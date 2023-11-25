#ifndef __PLATFORM_H__
#define __PLATFORM_H__

void resetCoordinates(void);
#ifdef _WIN32
void threadCreate(void (*function)(void *), void *args);
#else
void threadCreate(void *(*function)(void *), void *args);
#endif

#endif /* __PLATFORM_H__ */
