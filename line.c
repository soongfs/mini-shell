#include "line.h"
#include "builtin.h"
#include "launch.h"
#include <stdio.h>  //getline, stdin
#include <stdlib.h> //malloc
#include <string.h> //strtok, strcmp

char *mini_shell_read_line() {
    char *line = NULL;
    size_t bufsize;
    getline(&line, &bufsize, stdin);
    return line;
}

char **mini_shell_split_line(char *line) {
    int buffer_size = MINI_SHELL_TOK_BUFFER_SIZE, position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    token = strtok(line, MINI_SHELL_TOK_DELIM);
    while (token != NULL) {
        tokens[position++] = token;
        token = strtok(NULL, MINI_SHELL_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int mini_shell_execute(char **args) {
    if (args[0] == NULL)
        return 1;

    for (int i = 0; i < mini_shell_builtin_nums(); ++i) {
        if (strcmp(args[0], builtin_cmd[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return mini_shell_launch(args);
}
