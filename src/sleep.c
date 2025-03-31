#include <stddef.h>
#include <threads.h>
#include <time.h>

void sleepMS(int msec)
{
    struct timespec tosleep =
    {
        .tv_sec = msec / 1000,
        .tv_nsec = msec % 1000 * 1000000,
    };
    thrd_sleep(&tosleep, NULL);
}
