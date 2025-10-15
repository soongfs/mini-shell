#include "launch.h"
#include <stdio.h>     //perror
#include <stdlib.h>    //exit, EXIT_FAILURE
#include <sys/types.h> //pid_t
#include <sys/wait.h>  //waitpid
#include <unistd.h>    //fork, execvp

int mini_shell_launch(char **args) {
    // execvp
    pid_t pid, wpid;
    int status;
    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1)
            perror("mini_shell error at execvp");
        exit(EXIT_FAILURE);
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        return 1;
    }
}
