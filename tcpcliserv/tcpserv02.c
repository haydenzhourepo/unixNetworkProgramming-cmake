#include "unp.h"

int main(int argc, char **argv)
{
  int listenfd, connfd;
  pid_t childpid;
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr;
  void sig_child(int);

  Signal(SIGCHLD, sig_child);

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  Listen(listenfd, LISTENQ);

  for (;;){
    clilen = sizeof(cliaddr);
    if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0){
      if (errno == EINTR)
        continue;
      else
        err_sys("accept error");
    }

    if ( (childpid = fork()) == 0 ){ /* child process */
      Close(listenfd);
      str_echo(connfd);
      exit(EXIT_SUCCESS);
    }

    Close(connfd); /* parent closes connected socket */
  }
}