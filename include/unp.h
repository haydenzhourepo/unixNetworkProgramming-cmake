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
//#include <netinet/sctp.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <time.h>
#include <math.h>

#define MAXLINE 4096 /* max text line length */
#define LISTENQ 1024
#define SERV_PORT 9877

#ifndef INFTIM
#define INFTIM (-1)
#endif

typedef void Sigfunc(int);
#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))
Sigfunc *Signal(int signo, Sigfunc *func);

int Socket(int family, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *sockaddr, socklen_t sockaddr_len);
void Listen(int sockfd, int backlog);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Write(int fd, void *ptr, size_t nbytes);
void Close(int fd);
ssize_t Read(int fd, void *ptr, size_t nbytes);

void Writen(int fd, void *ptr, size_t nbytes);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Shutdown(int fd, int how);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
       struct timeval *timeout);

void
Sendto(int fd, const void *ptr, size_t nbytes, int flags,
       const struct sockaddr *sa, socklen_t salen);
ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
         struct sockaddr *sa, socklen_t *salenptr);

const char * Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
void Inet_pton(int family, const char* strptr, struct in_addr* addr);
char *
Sock_ntop(const struct sockaddr *sa, socklen_t salen);

void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);


// udp
void dg_cli(FILE *fp, int sockfd, struct sockaddr * sa, int sa_len);
void dg_echo(int sockfd, struct sockaddr* pcliaddr, socklen_t clilen);

// stdio
char * Fgets(char *ptr, int n, FILE *stream);
void Fputs(const char *ptr, FILE *stream);
FILE * Fopen(const char *filename, const char *mode);

ssize_t
Readline(int fd, void *ptr, size_t maxlen);

// error
void err_quit(const char *msg, ...);
void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);

#endif	/* __unp_h */