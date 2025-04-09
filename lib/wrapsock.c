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