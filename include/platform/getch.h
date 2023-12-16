#ifndef __GETCH_H__
#define __GETCH_H__

#ifdef _WIN32
#include <conio.h>
#define getch _getch
inline int getchInit(void) { return 0; }
#else
int getch(void);
int getchInit(void);
#endif /* _WIN32 */

#endif /* __GETCH_H__ */
