#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *cmd;
} HistEntry;

static char *ms_strdup(const char *s) {
    if (!s)
        return NULL;
    size_t n = strlen(s) + 1;
    char *p = (char *)malloc(n);
    if (p)
        memcpy(p, s, n);
    return p;
}

static HistEntry ring[HIST_SIZE];
static int h_start = 0;
static int h_size = 0;

void history_free_all(void) {
    for (int i = 0; i < h_size; ++i) {
        int idx = (h_start + i) % HIST_SIZE;
        free(ring[idx].cmd);
        ring[idx].cmd = NULL;
    }
    h_start = 0;
    h_size = 0;
}

int history_size(void) { return h_size; }

void history_add(const char *line_trimmed) {
    if (!line_trimmed || !*line_trimmed)
        return;
    char *copy = ms_strdup(line_trimmed);
    if (!copy)
        return;

    if (h_size < HIST_SIZE) {
        int idx = (h_start + h_size) % HIST_SIZE;
        ring[idx].cmd = copy;
        h_size++;
    } else {
        free(ring[h_start].cmd);
        ring[h_start].cmd = copy;
        h_start = (h_start + 1) % HIST_SIZE;
    }
}

void history_print(void) {
    for (int i = 0; i < h_size; ++i) {
        int idx = (h_start + i) % HIST_SIZE;
        const char *s = ring[idx].cmd ? ring[idx].cmd : "";
        printf("%2d  %s\n", i + 1, s);
    }
    fflush(stdout);
}

const char *history_get_n(int n) {
    if (n < 1 || n > h_size)
        return NULL;
    int idx = (h_start + (n - 1)) % HIST_SIZE;
    return ring[idx].cmd;
}
