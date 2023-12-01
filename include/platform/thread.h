#ifndef __THREAD_H__
#define __THREAD_H__

#ifdef _WIN32
#include <process.h>
#else
#include <pthread.h>
#include <stddef.h>
#endif /* _WIN32 */

#ifdef _WIN32
typedef void  ThreadR;
#define ThreadReturn return
#else
typedef void* ThreadR;
#define ThreadReturn return NULL
#endif /* _WIN32 */
typedef ThreadR (*Thread)(void *);

static inline void threadCreate(Thread function, void *args)
{
#ifdef _WIN32
    _beginthread(function, 0, args);
#else
    pthread_create(&(pthread_t){0}, 0, function, args);
#endif /* _WIN32 */
}

#endif /* __THREAD_H__ */
