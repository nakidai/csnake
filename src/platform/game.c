#ifdef _WIN32
void platformGameInit(void) {}
#else

#include <signal.h>
#include <stdlib.h>

#include "platform/getch.h"

void platformGameInit(void)
{
    getchInit();
    
    atexit(getchResetTerminalState);

    signal(SIGINT,  getchResetTerminalStateHandler);
    signal(SIGABRT, getchResetTerminalStateHandler);
    signal(SIGFPE,  getchResetTerminalStateHandler);
    signal(SIGILL,  getchResetTerminalStateHandler);
    signal(SIGSEGV, getchResetTerminalStateHandler);
    signal(SIGTERM, getchResetTerminalStateHandler);
}

#endif /* _WIN32 */
