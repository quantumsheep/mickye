#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <string.h>
#include <unistd.h>

#define console_err(msg) write(STDERR_FILENO, msg, strlen(msg))

#endif
