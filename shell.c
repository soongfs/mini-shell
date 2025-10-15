#include "line.h"
#include <stdio.h>  //printf
#include <stdlib.h> //free
#include <string.h> //strcat
#include <unistd.h> //getcwd

void mini_shell_loop(); // 主循环

int main(int argc, char *argv[]) {
    mini_shell_loop();
    return 0;
}

void mini_shell_loop() {
    char *line;
    char **args;
    int status;

    do {
        char path[100];
        getcwd(path, 100);
        char now[200] = "[mini-shell ";
        strcat(now, path);
        strcat(now, "]$ ");
        printf("%s", now);

        line = mini_shell_read_line();
        args = mini_shell_split_line(line);
        status = mini_shell_execute(args);

        free(line);
        free(args);
    } while (status);
}
