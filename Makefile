CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
INCLUDES = -Iinclude

SRC = main.c src/grid.c
TARGET = bin/biosim

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

clean:
	rm -rf bin

.PHONY: all clean