#include <time.h>

long long int getMS()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

void sleepMS(int msec)
{
    long long int end = getMS() + msec;
    while (getMS() < end);
}
