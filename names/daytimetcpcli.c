#include "unp.h"

int main(int argc, char **argv)
{
  int sockfd, n;
  char recvline [MAXLINE + 1];
  socklen_t len;
  struct sockaddr_storage ss;

  if (argc != 3)
    err_quit("usage: daytimetcpcli <hostname/Ipaddress> <service/port>");

  sockfd = Tcp_connect(argv[1], argv[2]);


  len = sizeof(ss);
  Getpeername(sockfd, (struct sockaddr *)&ss, &len);
  printf("connected to %s\n", Sock_ntop((struct sockaddr *)&ss, len));

  while ((n = Read(sockfd, recvline, MAXLINE)) > 0){
    recvline[n] = 0;
    Fputs(recvline, stdout);
  }

  exit(EXIT_SUCCESS);
}