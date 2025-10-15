#include "line.h"
#include "builtin.h"
#include "history.h"
#include "launch.h"
#include <stdio.h>  // getline, stdin, printf, perror
#include <stdlib.h> // malloc, free, exit
#include <string.h> // strtok, strcmp, strlen, memcpy

static char *ms_strdup(const char *s) {
    if (!s)
        return NULL;
    size_t n = strlen(s) + 1;
    char *p = (char *)malloc(n);
    if (p)
        memcpy(p, s, n);
    return p;
}

static void rstrip_newline(char *s) {
    if (!s)
        return;
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}

static int is_blank(const char *s) {
    if (!s)
        return 1;
    for (const char *p = s; *p; ++p) {
        if (*p != ' ' && *p != '\t' && *p != '\r' && *p != '\n')
            return 0;
    }
    return 1;
}

char *mini_shell_read_line() {
    char *line = NULL;
    size_t bufsize = 0;
    if (getline(&line, &bufsize, stdin) == -1) {
        if (line)
            free(line);
        return NULL;
    }
    return line;
}

char **mini_shell_split_line(char *line) {
    int bufsize = MINI_SHELL_TOK_BUFFER_SIZE;
    int position = 0;
    char **tokens = (char **)malloc(bufsize * sizeof(char *));
    if (!tokens)
        return NULL;

    char *tok = strtok(line, MINI_SHELL_TOK_DELIM);
    while (tok != NULL) {
        tokens[position++] = tok;
        if (position >= bufsize) {
            bufsize *= 2;
            char **tmp = (char **)realloc(tokens, bufsize * sizeof(char *));
            if (!tmp) {
                free(tokens);
                return NULL;
            }
            tokens = tmp;
        }
        tok = strtok(NULL, MINI_SHELL_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int mini_shell_execute(char **args) {
    if (args == NULL)
        return 1;
    if (args[0] == NULL)
        return 1;

    for (int i = 0; i < mini_shell_builtin_nums(); ++i) {
        if (strcmp(args[0], builtin_cmd[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return mini_shell_launch(args);
}

static int parse_bang_number(const char *s, int *out_n) {
    if (!s || s[0] != '!')
        return 0;
    if (s[1] == '\0')
        return 0;
    char *end = NULL;
    long val = strtol(s + 1, &end, 10);
    if (end && *end == '\0' && val > 0 && val <= 1000000) {
        *out_n = (int)val;
        return 1;
    }
    return 0;
}

int mini_shell_process_and_execute(char *line_raw) {
    if (!line_raw)
        return 0;
    rstrip_newline(line_raw);

    if (is_blank(line_raw)) {
        return 1;
    }

    int n = 0;
    if (line_raw[0] == '!' && parse_bang_number(line_raw, &n)) {
        const char *cmd = history_get_n(n);
        if (!cmd) {
            fprintf(stderr, "mini-shell: history: no such entry: %d\n", n);
            return 1;
        }
        printf("%s\n", cmd);
        fflush(stdout);

        char *dup = ms_strdup(cmd);
        if (!dup) {
            fprintf(stderr, "mini-shell: history: allocation failed\n");
            return 1;
        }
        history_add(cmd);

        char **args = mini_shell_split_line(dup);
        int status = mini_shell_execute(args);

        free(args);
        free(dup);
        return status;
    }

    history_add(line_raw);

    char *work = ms_strdup(line_raw);
    if (!work) {
        fprintf(stderr, "mini-shell: allocation failed\n");
        return 1;
    }
    char **args = mini_shell_split_line(work);
    int status = mini_shell_execute(args);
    free(args);
    free(work);
    return status;
}
