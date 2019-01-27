#ifndef _STREAMS_CONSOLE_H
#define _STREAMS_CONSOLE_H

#include <string.h>
#include <unistd.h>

#define console_err(msg) write(STDERR_FILENO, msg, strlen(msg))

#endif
