#include "unp.h"


#define MAXLINE 4096 /* max text line length */

void err_quit(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  vprintf(msg, args);
  va_end(args);
  exit(1);
}

static void
err_doit(int errnoflag, int error, const char*fmt, va_list ap){
  char buf[MAXLINE];
  vsnprintf(buf, MAXLINE, fmt, ap);
  if (errnoflag)
    snprintf(buf + strlen(buf), MAXLINE- strlen(buf), ": %s", strerror(error));

  strcat(buf, "\n");
  fflush(stdout);
  fputs(buf, stderr);
  fflush(NULL);
}

void err_sys(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  exit(1);
}