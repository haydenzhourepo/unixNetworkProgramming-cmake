#include "unp.h"

int main(int argc, char **argv)
{
  int listenfd, connfd;
  pid_t childpid;
  socklen_t chilen;
  struct sockaddr_un cliaddr, servaddr;
//  void sig_child(int);

  listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
  unlink(UNIXSTR_PATH);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sun_family = AF_LOCAL;
  strcpy(servaddr.sun_path, UNIXSTR_PATH);
  Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  Listen(listenfd, LISTENQ);
//  Signal(SIGCHLD, sig_child);

  for (;;){
    chilen = sizeof(cliaddr);
    if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &chilen)) < 0)
    {
      if (errno == EINTR)
        continue;
      else
        err_sys("accpet error");
    }

    if ((childpid = fork()) == 0){
      Close(listenfd);
      str_echo(connfd);
      exit(0);
    }
    Close(connfd);


  }
}