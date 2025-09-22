BUILD_DIR := build
BINARY    := game
CC        := gcc
CFLAGS    := -Wall -Wextra -O2
LIBS      := -lX11

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(BINARY)

$(BUILD_DIR)/$(BINARY): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: src/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

