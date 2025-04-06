//
// Created by mfkha on 4/24/2023.
//

#include "unp.h"


int main(int argc, char **argv)
{
  int listenfd, connfd;
  struct sockaddr_in servaddr;
  char buff[MAXLINE];
  time_t ticks;

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      err_sys("socket create error");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(11114);

  if (bind(listenfd, (struct sockaddr *)& servaddr, sizeof(servaddr)) == -1)
      err_sys("socket bind error");

  if (listen(listenfd, LISTENQ) == -1)
      err_sys("socket listen error");

  for(;;){
      if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == -1)
        err_sys("socket accept error");

      ticks = time(NULL);
      snprintf(buff, sizeof(buff), "%s\r\n", ctime(&ticks));

      send(connfd, buff, strlen(buff), 0);
      close(connfd);
  }
}