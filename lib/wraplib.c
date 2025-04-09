#include "unp.h"

const char * Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
  const char *ptr;
  if (strptr == NULL)
    err_quit("NULL 3rd argument to inet_ntop");
  if ((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
    err_sys("inet_ntop error");

  return ptr;
}