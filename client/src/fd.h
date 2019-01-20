#ifndef _FD_H
#define _FD_H

#define FD_CHUNK_SIZE ((size_t)8192)

#include <unistd.h>

#define fd_read(fd, data) read(fd, data, FD_CHUNK_SIZE)
#define fd_write(fd, data) write(fd, data, strlen(data))

#endif
