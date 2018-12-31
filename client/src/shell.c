#include <unistd.h>
#include "shell.h"

FILE*
open_shell (const char *cmd)
{
    int fd[2];
    int read_fd, write_fd;
    int pid;               

    /* First, create a pipe and a pair of file descriptors for its both ends */
    pipe(fd);
    read_fd = fd[0];
    write_fd = fd[1];

    /* Now fork in order to create process from we'll read from */
    pid = fork();
    if (pid == 0) {
        /* Child process */

        /* Close "read" endpoint - child will only use write end */
        close(read_fd);

        /* Now "bind" fd 1 (standard output) to our "write" end of pipe */
        dup2(write_fd,1);

        /* Close original descriptor we got from pipe() */
        close(write_fd);

        /* Execute command via shell - this will replace current process */
        execl("/bin/sh", "sh", "-c", cmd, NULL);

        /* Don't let compiler be angry with us */
        return NULL;
    } else {
        /* Parent */

        /* Close "write" end, not needed in this process */
        close(write_fd);

        /* Parent process is simpler - just create FILE* from file descriptor,
           for compatibility with popen() */
        return fdopen(read_fd, "r");
    }
}
