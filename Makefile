CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c99 \
          $(shell pkg-config --cflags sdl3 sdl3-ttf)

LDFLAGS = $(shell pkg-config --libs sdl3 sdl3-ttf)

INCLUDES = -Iinclude

SRC := $(wildcard src/*.c)
TARGET = bin/biosim

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf bin

.PHONY: all clean