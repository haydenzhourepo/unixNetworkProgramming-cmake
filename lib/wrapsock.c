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