CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lncurses

TARGET = game_of_life

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): game_of_life.c
	$(CC) $(CFLAGS) game_of_life.c -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

rebuild: clean all
