#include "unp.h"

int Socket(int family, int type, int protocol){
  int n;
  if ((n = socket(family, type, protocol)) < 0)
    err_sys("socket error");

  return n;
}

void Bind(int sockfd, const struct sockaddr *sockaddr, socklen_t sockaddr_len){
  if (bind(sockfd, sockaddr, sockaddr_len) != 0)
    err_sys("socket bind error");
}

void Listen(int sockfd, int backlog)
{
  if (listen(sockfd, backlog) != 0)
    err_sys("socket listen error");
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr){
  int n;
again:
  if ((n = accept(fd, sa, salenptr)) < 0){
#ifdef EPROTO
    if (errno == EPROTO || errno == ECONNABORTED)
#else
    if (errno == ECONNABORTED)
#endif
        goto again;
    else
      err_sys("socket accept error");
  }

  return n;
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
  if (connect(fd, sa, salen) < 0)
    err_sys("connect error");
}

void Shutdown(int fd, int how)
{
  if (shutdown(fd, how) < 0)
    err_sys("shutdown error");
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
       struct timeval *timeout)
{
  int		n;

  if ( (n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
    err_sys("select error");
  return(n);		/* can return 0 on timeout */
}

ssize_t
Recv(int fd, void *ptr, size_t nbytes, int flags)
{
  ssize_t		n;

  if ( (n = recv(fd, ptr, nbytes, flags)) < 0)
    err_sys("recv error");
  return(n);
}

ssize_t
Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
         struct sockaddr *sa, socklen_t *salenptr)
{
  ssize_t		n;

  if ( (n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
    err_sys("recvfrom error");
  return(n);
}

void
Send(int fd, const void *ptr, size_t nbytes, int flags)
{
  if (send(fd, ptr, nbytes, flags) != (ssize_t)nbytes)
    err_sys("send error");
}

void
Sendto(int fd, const void *ptr, size_t nbytes, int flags,
       const struct sockaddr *sa, socklen_t salen)
{
  if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
    err_sys("sendto error");
}

void
Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
  if (getpeername(fd, sa, salenptr) < 0)
    err_sys("getpeername error");
}

void
Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
  if (getsockname(fd, sa, salenptr) < 0)
    err_sys("getsockname error");
}

void
Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
  if (setsockopt(fd, level, optname, optval, optlen) < 0)
    err_sys("setsockopt error");
}