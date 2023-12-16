#ifndef _WIN32
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

static struct termios DefaultState = {0};

int getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
    old.c_lflag    &= ~ECHO;     // local modes = Disable echo. 
    old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
    old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag    |= ICANON;    // local modes = Canonical mode
    old.c_lflag    |= ECHO;      // local modes = Enable echo. 
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return (int)buf;
}

static void resetTerminalState(void)
{
    tcsetattr(0, TCSANOW, &DefaultState);
}

int getchInit(void)
{
    tcgetattr(0, &DefaultState);
    return atexit(resetTerminalState);
}

#endif /* !_WIN32 */
