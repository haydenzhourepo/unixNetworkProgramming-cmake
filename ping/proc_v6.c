#include "ping.h"

void proc_v6(char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv)
{
#ifdef AF_INET6
  double rtt;
  struct icmp6_hdr *icmp6;
  struct timeval *tvsend;
  struct cmsghdr *cmsg;
  int hlim;

  icmp6 = (struct icmp6_hdr *)ptr;
  if (len < 8)
    return;

  if (icmp6->icmp6_type == ICMP6_ECHO_REPLY)
  {
    if (icmp6->icmp6_id != pid)
      return;
    if (len < 16)
      return;

    tvsend = (struct timeval *)(icmp6 + 1);
    tv_sub(tvrecv, tvsend);
    rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

    hlim = -1;
    for (cmsg = CMSG_FIRSTHDR(msg); cmsg != NULL; cmsg = CMSG_NXTHDR(msg, cmsg))
    {
      if (cmsg->cmsg_type == IPPROTO_IPV6 && cmsg->cmsg_type == IPV6_HOPLIMIT) {
        hlim = *(u_int32_t *)CMSG_DATA(cmsg);
        break;
      }
    }

    printf("%d bytes from %s: seq=%u, hlim=",
           len, Sock_ntop_host(pr->sarecv, pr->salen),
           icmp6->icmp6_seq);
    if (hlim == -1)
      printf("???");
    else
      printf("%d", hlim);
    printf(", rtt=%.3f ms\n", rtt);
  }else if (verbose)
  {
    printf(" %d bytes from %s: type = %d, code = %d\n",
           len, Sock_ntop_host(pr->sarecv, pr->salen),
           icmp6->icmp6_type, icmp6->icmp6_code);
  }
#endif
}