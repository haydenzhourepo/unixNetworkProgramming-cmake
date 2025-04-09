#include "unp.h"

void Write(int fd, void *ptr, size_t nbytes)
{
  if (write(fd, ptr, nbytes) != nbytes)
    err_sys("write error");
}


void
Close(int fd)
{
  if (close(fd) == -1)
    err_sys("close error");
}