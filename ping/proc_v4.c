#include "ping.h"

/*
 *  +--------------------------------------------------------+
    |                           len                          |
    +----------------------------+--------------------------+|
    |           hlen1            |         icmplen           |
    +----------------------------+--------------------------+|
    | IPv4 header | IPv4 options | ICMPv4 header | ICMP data |
    |    20 bytes |  0 - 40 bytes|     8 bytes   |           |
    |             |              |               |           |
    +-------------+--------------+---------------+-----------+
    ^                            ^
    | ip pointer                 | icmp pointer
 *
 */
void proc_v4(char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv)
{
  int hlenl, icmplen;
  double rtt;
  struct ip *ip;
  struct icmp *icmp;
  struct timeval *tvsend;

  ip = (struct ip *)ptr;
  hlenl = ip->ip_hl << 2;

  if (ip->ip_p != IPPROTO_ICMP)
    return;

  icmp = (struct icmp *)(ptr +hlenl);   // start of ICMP header
  if ((icmplen = len - hlenl) < 8)      // malformed package
    return;

  if (icmp->icmp_type == ICMP_ECHOREPLY)
  {

    if (icmp->icmp_id != pid)        // not a response to our ECHO_REQUEST
      return;
    if (icmplen <16)                  // not enough data to use
      return;

    tvsend = (struct timeval *)icmp->icmp_data;
    tv_sub(tvrecv, tvsend);
    rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;
    printf("%d bytes from %s: seq=%u, ttl= %d, rtt = %.3f ms\n",
           icmplen, Sock_ntop_host(pr->sarecv, pr->salen),
           icmp->icmp_seq, ip->ip_ttl, rtt);


  } else if (verbose)
  {
    printf(" %d bytes from %s:type = %d, code = %d\n",
           icmplen, Sock_ntop_host(pr->sarecv, pr->salen),
           icmp->icmp_type, icmp->icmp_code);
  }
}