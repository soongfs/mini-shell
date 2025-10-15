#ifndef MINI_SHELL_HISTORY_H
#define MINI_SHELL_HISTORY_H

// Keep last 10 commands
#define HIST_SIZE 10

// Add a command (line must be a normal C string; function duplicates it)
void history_add(const char *line_trimmed);

// Print history as " 1  cmd"
void history_print(void);

// Get the n-th (1..size) history entry; returns const char* owned by history
const char *history_get_n(int n);

// Free any allocated memory at program end
void history_free_all(void);

// Current history size (<= HIST_SIZE)
int history_size(void);

#endif // MINI_SHELL_HISTORY_H
