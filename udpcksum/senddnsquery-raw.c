#include "udpcksum.h"

void send_dns_query(void)
{
  size_t nbytes;
  char *buf, *ptr;
  buf = malloc(sizeof(struct iphdr) + sizeof(struct udphdr) +200);
  ptr = buf +sizeof(struct iphdr) + sizeof(struct udphdr);
  memset(buf, 0, sizeof(struct iphdr) + sizeof(struct udphdr) + 200);

  *((uint16_t *) ptr) = htons(1234);	/* identification */
  ptr += 2;
  *((uint16_t *) ptr) = htons(0x0100);	/* flags: recursion desired */
  ptr += 2;
  *((uint16_t *) ptr) = htons(1);		/* # questions */
  ptr += 2;
  *((uint16_t *) ptr) = 0;			/* # answer RRs */
  ptr += 2;
  *((uint16_t *) ptr) = 0;			/* # authority RRs */
  ptr += 2;
  *((uint16_t *) ptr) = 0;			/* # additional RRs */
  ptr += 2;

  memcpy(ptr, "\001a\014root-servers\003net\000", 20);
  ptr += 20;
  *((uint16_t *) ptr) = htons(1);		/* query type = A */
  ptr += 2;
  *((uint16_t *) ptr) = htons(1);		/* query class = 1 (IP addr) */
  ptr += 2;

  nbytes = (ptr-buf) - sizeof(struct udphdr) - sizeof(struct iphdr);

  udp_write(buf, nbytes);
  if (verbose)
    printf("sent: %d bytes of data\n", nbytes);



}