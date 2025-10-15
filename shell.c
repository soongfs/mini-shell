#include "history.h"
#include "line.h"
#include <stdio.h>  // printf
#include <stdlib.h> // free, exit
#include <unistd.h> // getcwd

void mini_shell_loop(void) {
    char *line = NULL;
    int status = 1;
    do {
        char path[256] = {0};
        if (!getcwd(path, sizeof(path) - 1)) {
            // fallback
            snprintf(path, sizeof(path), "?");
        }
        char prompt[512];
        snprintf(prompt, sizeof(prompt), "[mini-shell %s]$ ", path);
        fputs(prompt, stdout);
        fflush(stdout);

        line = mini_shell_read_line();
        if (!line) {
            putchar('\n');
            break;
        }

        status = mini_shell_process_and_execute(line);

        free(line);
    } while (status);

    history_free_all();
}

int main(int argc, char *argv[]) {
    mini_shell_loop();
    return 0;
}
