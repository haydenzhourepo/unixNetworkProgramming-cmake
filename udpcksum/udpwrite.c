#include	"udpcksum.h"

/* include open_output_raw */
int		rawfd;			/* raw socket to write on */

void
open_output(void)
{
  int	on=1;
  /*
	 * Need a raw socket to write our own IP datagrams to.
	 * Process must have superuser privileges to create this socket.
	 * Also must set IP_HDRINCL so we can write our own IP headers.
   */
  rawfd = Socket(dest->sa_family, SOCK_RAW, IPPROTO_UDP);

  Setsockopt(rawfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));
}
/* end open_output_raw */


/*
 * "buf" points to an empty IP/UDP header,
 * followed by "ulen" bytes of user data.
 */

/* include udp_write */
void
udp_write(char *buf, int userlen)
{
  struct udphdr		*uh;
  struct iphdr		*ip;


  /* 4fill in and checksum UDP header */
  ip = (struct iphdr *) buf;
  uh = (struct udphdr *) (buf + sizeof(*ip));

//  bzero(ip, sizeof(*ip));
//  bzero(uh, sizeof(*uh));

//  uh->source = htons(((struct soc
  uh->source = ((struct sockaddr_in *)local)->sin_port;
  uh->dest = ((struct sockaddr_in *)dest)->sin_port;
  u_short uhlen = sizeof(*uh) + userlen;
  uh->len = htons(uhlen);
  uh->uh_sum = 0;
  uh->check = 0;
//  if (zerosum == 0) {
//    uh->uh_sum = in_cksum((u_int16_t *) uh, (userlen + sizeof(struct udphdr)));
//  }

  ip->version = IPVERSION;
  ip->ihl = sizeof(*ip) >> 2;
  ip->tot_len = htons(sizeof(*ip) + sizeof(*uh) + userlen);
  ip->ttl = TTL_OUT;
  ip->protocol = IPPROTO_UDP;
  ip->saddr = ((struct sockaddr_in *)local)->sin_addr.s_addr;
  ip->daddr = ((struct sockaddr_in *)dest)->sin_addr.s_addr;

  printf("send package\n");
  // 发送数据包

  Sendto(rawfd, buf, sizeof(*ip) + sizeof(*uh) + userlen, 0, dest, destlen);


}
/* end udp_write */
