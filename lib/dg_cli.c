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