#include "unp.h"

// Ubuntu not support sctp
int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in servaddr;
//  struct sctp_event_subscribe events;
  int echo_to_all = 0;

  return EXIT_SUCCESS;
}