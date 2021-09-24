
#ifdef linux

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>

bool _kbhit(void);
int _getch(void);

// #define CMIN 1

// #ifdef CTIME
// #undef CTIME
// #endif

// #define CTIME 1

#endif