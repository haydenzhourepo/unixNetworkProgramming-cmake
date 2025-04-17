#include "unp.h"
#include "sys/time.h"
#include "netinet/ip.h"
#include <netinet/ip_icmp.h>
#include <netinet/ip6.h>
#include <netinet/icmp6.h>


#define BUFSIZE 1500

extern char sendbuf[BUFSIZE];

extern int datalen;
extern char *host;
extern int nsent;
extern pid_t pid;
extern int sockfd;
extern int verbose;

void init_v6(void);
void proc_v4(char *, ssize_t, struct msghdr *, struct timeval *);
void proc_v6(char *, ssize_t, struct msghdr *, struct timeval *);
void send_v4(void);
void send_v6(void);
void readloop(void);
void sig_alrm(int);
void tv_sub(struct timeval *, struct timeval *);

struct proto {
  void (*fproc) (char*, ssize_t, struct msghdr *, struct timeval*);
  void (*fsend) (void);
  void (*finit) (void);
  struct sockaddr *sasend;  // sockaddr{} for send, from getaddrinfo
  struct sockaddr *sarecv;   // sockaddr{} for receiving
  socklen_t salen;
  int icmpproto;              // IPPROTO_xxx value for ICMP
};


extern struct proto *pr;
