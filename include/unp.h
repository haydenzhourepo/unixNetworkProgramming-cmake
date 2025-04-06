/* include unph */
/* Our own header.  Tabs are set for 4 spaces, not 8 */

#ifndef	__unp_h
#define	__unp_h
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAXLINE 4096 /* max text line length */
#define LISTENQ 1024


void err_quit(const char *msg, ...);

static void
err_doit(int errnoflag, int error, const char*fmt, va_list ap);

void err_sys(const char *fmt, ...);

#endif	/* __unp_h */