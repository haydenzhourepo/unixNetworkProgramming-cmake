#include "unp.h"

int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in servaddr;

  if (argc != 2)
    err_quit("usage: udpcli <Ip address>");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

  broadcase_gd_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}