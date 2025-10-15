#ifndef MINI_SHELL_BUILTIN_H
#define MINI_SHELL_BUILTIN_H

extern char *builtin_cmd[];
extern int (*builtin_func[])(char **);

int mini_shell_builtin_nums();

int mini_shell_help(char **args);
int mini_shell_cd(char **args);
int mini_shell_pwd(char **args);
int mini_shell_history(char **args);
int mini_shell_exit(char **args);

#endif // MINI_SHELL_BUILTIN_H
