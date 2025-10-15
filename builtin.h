extern char *builtin_cmd[];

extern int (*builtin_func[])(char **);

/**
 * @brief 返回内置命令个数
 *
 * @return int 内置命令个数
 */
int mini_shell_builtin_nums();

/**
 * @brief 内置help命令
 *
 * @param args 命令参数
 * @return int 运行状态
 */
int mini_shell_help(char **args);

/**
 * @brief 内置cd命令
 *
 * @param args 命令参数
 * @return int 运行状态
 */
int mini_shell_cd(char **args);

int mini_shell_pwd(char **args);

/**
 * @brief 内置exit命令
 *
 * @param args 命令参数
 * @return int 运行状态
 */
int mini_shell_exit(char **args);
