CC = gcc

CPPFLAGS = -Iinclude $(shell pkg-config --cflags sdl3 sdl3-ttf)
CFLAGS   = -Wall -Wextra -Werror -std=c17
LDLIBS   = $(shell pkg-config --libs sdl3 sdl3-ttf)

INCLUDES = -Iinclude

SRC := $(wildcard src/*.c)
TARGET = bin/biosim

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) -o $@ $(LDLIBS)

clean:
	rm -rf bin

.PHONY: all clean
