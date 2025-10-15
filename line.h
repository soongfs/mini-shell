#define MINI_SHELL_TOK_DELIM " \t\r\n"
#define MINI_SHELL_TOK_BUFFER_SIZE 64

/**
 * @brief 读取命令
 *
 * @return char* 得到的命令
 */
char *mini_shell_read_line();

/**
 * @brief 拆分命令
 *
 * @param line 输入命令
 * @return char** 参数数组
 */
char **mini_shell_split_line(char *line);

/**
 * @brief 执行命令行
 *
 * @param args 命令参数
 * @return int 运行状态
 */
int mini_shell_execute(char **args);
