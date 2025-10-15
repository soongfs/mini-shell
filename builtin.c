#include "builtin.h"
#include "history.h"
#include <errno.h>
#include <stdio.h>   // printf, fprintf, perror
#include <stdlib.h>  // strtol, free
#include <string.h>  // strcmp, strerror
#include <unistd.h>  // getcwd, chdir

char *builtin_cmd[] = {"help", "cd", "pwd", "history", "exit"};

int (*builtin_func[])(char **) = {
    &mini_shell_help,
    &mini_shell_cd,
    &mini_shell_pwd,
    &mini_shell_history,
    &mini_shell_exit
};

int mini_shell_builtin_nums() {
    return sizeof(builtin_cmd) / sizeof(builtin_cmd[0]);
}

int mini_shell_help(char **args) {
    (void)args; // unused
    puts("Mini Shell - builtins:");
    puts("  help                 Show this help");
    puts("  cd [dir]             Change directory (default: $HOME)");
    puts("  pwd                  Print current directory");
    puts("  history              Show last 10 valid commands");
    puts("  exit [status]        Exit shell with optional status");
    return 1;
}

int mini_shell_cd(char **args) {
    // args[0] = "cd", args[1] = path?, args[2] = maybe extra
    if (args[1] && args[2]) {
        fprintf(stderr, "mini-shell: cd: too many arguments\n");
        return 1;
    }
    const char *target = args[1];
    if (!target || !*target) {
        target = getenv("HOME");
        if (!target) target = "/";
    }
    if (chdir(target) != 0) {
        fprintf(stderr, "mini-shell: cd: %s: %s\n", target, strerror(errno));
    }
    return 1;
}

int mini_shell_pwd(char **args) {
    if (args[1]) {
        fprintf(stderr, "mini-shell: pwd: no arguments expected\n");
        return 1;
    }
    char *cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("mini-shell: pwd");
        return 1;
    }
    printf("%s\n", cwd);
    free(cwd);
    return 1;
}

int mini_shell_history(char **args) {
    if (args[1]) {
        fprintf(stderr, "mini-shell: history: no arguments expected\n");
        return 1;
    }
    history_print();
    return 1;
}

int mini_shell_exit(char **args) {
    // exit [status]
    if (!args[1]) {
        return 0; // normal exit
    }
    if (args[2]) {
        fprintf(stderr, "mini-shell: exit: too many arguments\n");
        // do not exit shell on error; continue
        return 1;
    }
    char *end = NULL;
    long v = strtol(args[1], &end, 10);
    if (end && *end == '\0') {
        // encode exit status in return value? our loop exits on 0, so just exit here:
        // We'll use a convention: return 0 still, but set _Exit
        // Simpler: print a message and exit process directly.
        // However, original framework expects return 0 to stop loop; no channel to pass status.
        // We'll just exit immediately:
        _Exit((int)(v & 0xFF));
    } else {
        fprintf(stderr, "mini-shell: exit: numeric argument required: %s\n", args[1]);
        return 1;
    }
}
