#include "unp.h"

void dg_cli(FILE *fp, int sockfd, struct sockaddr * sa, int sa_len)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];
  while (Fgets(sendline, MAXLINE, fp) != NULL)
  {
    Sendto(sockfd, sendline, strlen(sendline), 0, sa, sa_len);

    n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
    recvline[n] = 0;
    Fputs(recvline, stdout);
  }
}

static void recvfrom_alarm(int signo);

void broadcase_gd_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
  int n;
  const int on = 1;
  char sendline[MAXLINE], recvline[MAXLINE +1];
  socklen_t len;
  struct sockaddr *preply_addr;

  preply_addr = malloc(servlen);

  Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

  Signal(SIGALRM, recvfrom_alarm);
  while (Fgets(sendline, MAXLINE, fp) != NULL){
    Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
    alarm(5);
    for (;;)
    {
      len = servlen;
      n = recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
      if (n < 0){
        if (errno == EINTR)
          break;
        else
          err_sys("recvfrom error");
      } else {
        recvline[n] = 0;
        printf("from %s: %s", Sock_ntop_host(preply_addr, len), recvline);
      }
    }
  }


  free(preply_addr);
}

static void recvfrom_alarm(int signo)
{
  return;
}