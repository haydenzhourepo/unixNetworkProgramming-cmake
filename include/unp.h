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
#include <signal.h>
#include <wait.h>
#include <time.h>

#define MAXLINE 4096 /* max text line length */
#define LISTENQ 1024
#define SERV_PORT 9877

typedef void Sigfunc(int);
Sigfunc *Signal(int signo, Sigfunc *func);

int Socket(int family, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *sockaddr, socklen_t sockaddr_len);
void Listen(int sockfd, int backlog);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Write(int fd, void *ptr, size_t nbytes);
void Close(int fd);

void Writen(int fd, void *ptr, size_t nbytes);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);

const char * Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
void Inet_pton(int family, const char* strptr, struct in_addr* addr);
char *sock_ntop(const struct sockaddr *sockaddr, socklen_t addrlen);


void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);


// stdio
char * Fgets(char *ptr, int n, FILE *stream);
void Fputs(const char *ptr, FILE *stream);
FILE * Fopen(const char *filename, const char *mode);

ssize_t
Readline(int fd, void *ptr, size_t maxlen);

// error
void err_quit(const char *msg, ...);
static void
err_doit(int errnoflag, int error, const char*fmt, va_list ap);

void err_sys(const char *fmt, ...);

#endif	/* __unp_h */