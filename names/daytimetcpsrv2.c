#include "unp.h"

int main(int argc, char **argv)
{
  int listenfd, connfd;
  socklen_t len;
  char buff[MAXLINE];
  time_t ticks;
  struct sockaddr_storage cliaddr;

  if (argc == 2)
    listenfd = Tcp_listen(NULL, argv[1], NULL);
  else if (argc == 3)
    listenfd = Tcp_listen(argv[1], argv[2], NULL);
  else
    err_quit("usage: daytimetcpsrv2 [host] <service or port#>");

  for (;;)
  {
    len = sizeof(cliaddr);
    connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &len);
    printf("connection from %s\n", Sock_ntop((struct sockaddr *)&cliaddr, len));

    ticks = time(NULL);
    snprintf(buff, sizeof (buff), "%.24s\r\n", ctime (&ticks) ) ;
    Write(connfd, buff, strlen (buff) ) ;

    Close (connfd);
  }
}