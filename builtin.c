#include "builtin.h"
#include <stdio.h>  //perror
#include <unistd.h> //NULL, getcwd

char *builtin_cmd[] = {"help", "cd", "pwd", "exit"};

int (*builtin_func[])(char **) = {&mini_shell_help, &mini_shell_cd,
                                  mini_shell_pwd, &mini_shell_exit};

int mini_shell_builtin_nums() {
    return sizeof(builtin_cmd) / sizeof(builtin_cmd[0]);
}

int mini_shell_help(char **args) {
    puts("This is My shell");
    puts("Here builtin cmd");
    for (int i = 0; i < mini_shell_builtin_nums(); i++) {
        printf("%s\n", builtin_cmd[i]);
    }
    return 1;
}

int mini_shell_cd(char **args) {
    if (args[1] == NULL) {
        perror("mini_shell error at cd, lack of args\n");
    } else {
        if (chdir(args[1]) != 0)
            perror("mini_shell error at chdir\n");
    }
    return 1;
}

int mini_shell_pwd(char **args) {
    char *cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("mini-shell: pwd");
    }
    printf("%s\n", cwd);
    // free(cwd);
    return 1;
}

int mini_shell_exit(char **args) { return 0; }
