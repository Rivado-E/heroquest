BUILD_DIR := build
BINARY    := game
CC        := gcc
CFLAGS    := -std=c99 -Wall -Wextra -O2 -Iinclude
LIBS      := -lX11

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(BINARY)

$(BUILD_DIR)/$(BINARY): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: src/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BUILD_DIR)/$(BINARY)
	./$(BUILD_DIR)/$(BINARY)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean $(BUILD_DIR)/$(BINARY)

.PHONY: all clean

