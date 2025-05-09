#include "udpcksum.h"

#define CMD "udp and src host %s and src port %d"


char * find_device(char *errbuf);

void open_pcap(void)
{


  uint32_t localnet, netmask;
  char cmd[MAXLINE], errbuf[PCAP_ERRBUF_SIZE],
      str1[INET_ADDRSTRLEN], str2[INET_ADDRSTRLEN];
  struct bpf_program fcode;

  if (device == NULL)
    device = find_device(errbuf);
  printf("device = %s\n", device);

  // hardcode promisc=0, to_ms=500
  if ((pd= pcap_open_live(device, snaplen, 0, 500, errbuf)) == NULL)
    err_quit("pcap_open_live: %s", errbuf);

  if (pcap_lookupnet(device, &localnet, &netmask, errbuf) < 0)
    err_quit("pcap_lookupnet: %s", errbuf);

  if (verbose)
    printf("localnet = %s, netmask = %s\n", Inet_ntop(AF_INET, &localnet, str1, sizeof(str1)), Inet_ntop(AF_INET, &netmask, str2, sizeof(str2)));

  snprintf(cmd, sizeof(cmd), CMD, Sock_ntop_host(dest, destlen), ntohs(sock_get_port(dest, destlen)));

  if (verbose)
    printf("cmd = %s\n", cmd);
  if (pcap_compile(pd, &fcode, cmd, 0, netmask) < 0)
    err_quit("pcap_compile: %s", pcap_geterr(pd));

  if (pcap_setfilter(pd, &fcode) < 0)
    err_quit("pcap_setfilter: %s", pcap_geterr(pd));

  if ((datalink = pcap_datalink(pd)) < 0)
    err_quit("pcap_datalink: %s", pcap_geterr(pd));

  if (verbose)
    printf("datalink = %d\n", datalink);

}

#ifdef USE_PCAP_LOOKUPDEV
char * find_device(char *errbuf){
  char * d;
  if ((d = pcap_lookupdev(errbuf)) == NULL)
    err_quit("pcap_lookup: %s", errbuf);
  return d;
}
#else
char * find_device(char *errbuf){
  pcap_if_t *alldevs;
  char *d;

  if (pcap_findalldevs(&alldevs, errbuf) == -1)
    err_quit("pcap_findalldevs: %s", errbuf);

  d = strdup(alldevs->name);
  pcap_freealldevs(alldevs);

  return d;
}
#endif


char *
next_pcap(int *len)
{
  char		        *ptr;
  struct pcap_pkthdr	hdr;

  /* 4keep looping until packet ready */
  while ( (ptr = (char *) pcap_next(pd, &hdr)) == NULL)
    ;

  *len = hdr.caplen;	/* captured length */
  return(ptr);
}