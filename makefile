TARGET = mini_shell
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRCS = builtin.c launch.c line.c shell.c history.c
OBJS = $(SRCS:.c=.o)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
