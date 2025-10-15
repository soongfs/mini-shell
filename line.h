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

/**
 * @brief 处理原始输入行（包含 !n 展开与历史写入）并执行
 *
 * @param line_raw 原始行（带或不带换行）
 * @return int 状态；1 继续循环，0 退出
 */
int mini_shell_process_and_execute(char *line_raw);
