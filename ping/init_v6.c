#include "ping.h"

void init_v6()
{
  int on = 1;
  if (verbose == 0)
  {
    // install a filter that only passed ICMP6_ECHO_ERPLY unless verbose
    struct icmp6_filter myfilt;
    ICMP6_FILTER_SETBLOCKALL(&myfilt);
    ICMP6_FILTER_SETPASS(ICMP6_ECHO_REPLY, &myfilt);
    setsockopt(sockfd, IPPROTO_IPV6, ICMP6_FILTER, &myfilt, sizeof(myfilt));
  }

#ifdef IPV6_RECVHOPLIMIT
  setsockopt(sockfd, IPPROTO_IPV6, IPV6_RECVHOPLIMIT, &on, sizeof(on));
#else
  setsockopt(sockfd, IPPROTO_IPV6, IPV6_HOPLIMIT, &on, sizeof(on));
#endif
}