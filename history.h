#ifndef MINI_SHELL_HISTORY_H
#define MINI_SHELL_HISTORY_H

#define HIST_SIZE 10

void history_add(const char *line_trimmed);

void history_print(void);

const char *history_get_n(int n);

void history_free_all(void);

int history_size(void);

#endif // MINI_SHELL_HISTORY_H
