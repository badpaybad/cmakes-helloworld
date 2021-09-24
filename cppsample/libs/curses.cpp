
#ifdef linux

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
/*
* kbhit() -- a keyboard lookahead monitor
*
* returns the number of characters available to read.
*/
bool _kbhit(void)
{
    int count = 0;
    int error;
    static struct termios Otty, Ntty;

    tcgetattr(STDIN_FILENO, &Otty);
    Ntty = Otty;

    Ntty.c_lflag &= ~ICANON; /* raw mode */
    Ntty.c_cc[VMIN] = CMIN; /* minimum chars to wait for */
    Ntty.c_cc[VTIME] = CTIME; /* minimum wait time */

    if (0 == (error = tcsetattr(STDIN_FILENO, TCSANOW, &Ntty))) {
    struct timeval tv;
    error += ioctl(STDIN_FILENO, FIONREAD, &count);
    error += tcsetattr(STDIN_FILENO, TCSANOW, &Otty);
    /* minimal delay gives up cpu time slice, and
    * allows use in a tight loop */
    tv.tv_sec = 0;
    tv.tv_usec = 10;
    select(1, NULL, NULL, NULL, &tv);
    }

    return (error == 0 ? count : -1 );
}

/*
* getch() -- a blocking single character input from stdin
*
* Returns a character, or -1 if an input error occurs.
*
* Conditionals allow compiling with or without echoing of
* the input characters, and with or without flushing
* pre-existing existing buffered input before blocking.
*
*/
int _getch(void)
{
    char ch;
    int error;
    static struct termios Otty, Ntty;

    fflush(stdout);
    tcgetattr(STDIN_FILENO, &Otty);
    Ntty = Otty;

    Ntty.c_lflag &= ~ICANON; /* line settings */

    #if 1
    /* disable echoing the char as it is typed */
    Ntty.c_lflag &= ~ECHO; /* disable echo */
    #else
    /* enable echoing the char as it is typed */
    Ntty.c_lflag |= ECHO; /* enable echo */
    #endif

    Ntty.c_cc[VMIN] = CMIN; /* minimum chars to wait for */
    Ntty.c_cc[VTIME] = CTIME; /* minimum wait time */

    #if 1
    /*
    * use this to flush the input buffer before
    * blocking for new input
    */
    #define FLAG TCSAFLUSH
    #else
    /*
    * use this to return a char from the current input buffer,
    * or block if no input is waiting.
    */
    #define FLAG TCSANOW

    #endif

    if (0 == (error = tcsetattr(STDIN_FILENO, FLAG, &Ntty))) {
    /* get a single character from stdin */
    error = read(STDIN_FILENO, &ch, 1 );
    /* restore old settings */
    error += tcsetattr(STDIN_FILENO, FLAG, &Otty);
    }

    return (error == 1 ? (int) ch : -1 );
}

#endif