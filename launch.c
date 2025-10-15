#include "launch.h"
#include <errno.h>
#include <stdio.h>     // fprintf, perror
#include <stdlib.h>    // exit, EXIT_FAILURE
#include <string.h>    // strerror
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // waitpid, WIF*
#include <unistd.h>    // fork, execvp, _exit

int mini_shell_launch(char **args) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "mini-shell: fork: %s\n", strerror(errno));
        return 1;
    }
    if (pid == 0) {
        execvp(args[0], args);
        int e = errno;
        if (e == ENOENT) {
            fprintf(stderr, "mini-shell: command not found: %s\n", args[0]);
        } else if (e == EACCES) {
            fprintf(stderr, "mini-shell: permission denied: %s\n", args[0]);
        } else if (e == ENOEXEC) {
            fprintf(stderr, "mini-shell: exec format error: %s\n", args[0]);
        } else {
            fprintf(stderr, "mini-shell: execvp(%s) failed: %s\n", args[0],
                    strerror(e));
        }
        _exit(127);
    } else {
        int status = 0;
        while (1) {
            pid_t w = waitpid(pid, &status, 0);
            if (w == -1) {
                if (errno == EINTR)
                    continue;
                fprintf(stderr, "mini-shell: waitpid: %s\n", strerror(errno));
                break;
            }
            if (WIFEXITED(status) || WIFSIGNALED(status))
                break;
        }
        return 1;
    }
}
