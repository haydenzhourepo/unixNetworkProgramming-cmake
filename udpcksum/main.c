#include "udpcksum.h"

// define global variables
struct sockaddr *dest, *local;
struct sockaddr_in locallookup;
socklen_t destlen, locallen;

int datalink;
char *device;
pcap_t *pd;
int snaplen = 200;
int verbose;
int zerosum;

static void usage(const char *);

int main(int argc, char **argv)
{
  int c, lopt = 0;
  char *ptr, localname[1024], *localport;
  struct addrinfo *aip;
  opterr = 0;
  while ((c = getopt(argc, argv, "0i:l:v")) != -1){
    switch (c) {
    case '0':
      zerosum = 1;
      break;
    case 'i':            // pcap device
      device = optarg;
      break;
    case 'l':             // local IP address and port
      if ((ptr = strrchr(optarg, '.')) == NULL)
        usage("invalid -l option");
      *ptr++ = 0;  // null replaces final period

      localport = ptr;
      strncpy(localname, optarg, sizeof(localname));
      lopt = 1;
      break;
    case 'v':
      verbose = 1;
      break;
    case '?':
      usage("unrecognized option");
    }
  }

  if (optind != argc - 2)
    usage("missing <host> and/or <serv>");

  // convert destination name and service
  aip = Host_serv(argv[optind], argv[optind + 1], AF_INET, SOCK_DGRAM);
  dest = aip->ai_addr;
  destlen = aip->ai_addrlen;

  // Need local IP address for source IP address for UDP datagrams.
  // Can't specify 0 and let IP choose, as we need to know it for
  // the pseudoheader to calculate the UDP checksum.
  // If -l option supplied, then use those values; otherwise,
  // connect a UD socket to the destination to determine the right source address.

  if (lopt){
    // convert local name and service
    aip = Host_serv(localname, localport, AF_INET, SOCK_DGRAM);
    local = aip->ai_addr;
    locallen = aip->ai_addrlen;
  } else {
    int s;
    s = Socket(AF_INET, SOCK_DGRAM, 0);
    Connect(s, dest, destlen);
    // kernel chooses correct local address for dest
    locallen = sizeof(locallookup);
    local = (struct sockaddr *)&locallookup;
    Getsockname(s, local, &locallen);
    if (locallookup.sin_addr.s_addr == htonl(INADDR_ANY))
      err_quit("Can't determine local address - use -l \n");
    close(s);
  }

  // open output, either raw socket or libnet
  open_output();

  // open packet capture device
  open_pcap();

  // don't need superuser privileges anymore
  setuid(getuid());

  Signal(SIGTERM, cleanup);
  Signal(SIGINT, cleanup);
  Signal(SIGHUP, cleanup);

  test_udp();

  cleanup(0);

  return EXIT_SUCCESS;
}

static void usage(const char *msg){
  err_quit(msg);
}