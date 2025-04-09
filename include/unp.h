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

int Socket(int family, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *sockaddr, socklen_t sockaddr_len);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Write(int fd, void *ptr, size_t nbytes);
void Close(int fd);

const char * Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
char *sock_ntop(const struct sockaddr *sockaddr, socklen_t addrlen);

void err_quit(const char *msg, ...);

static void
err_doit(int errnoflag, int error, const char*fmt, va_list ap);

void err_sys(const char *fmt, ...);

#endif	/* __unp_h */