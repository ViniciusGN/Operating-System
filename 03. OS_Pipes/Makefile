CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = bin
SIMPLE_BUILD_DIR = $(BUILD_DIR)/simple
FSIEVE_BUILD_DIR = $(BUILD_DIR)/fsieve

SIMPLE_SRCS = $(SRC_DIR)/simple/main.c
FSIEVE_SRCS = $(SRC_DIR)/fsieve/fsieve.c $(SRC_DIR)/fsieve/main.c

SIMPLE_OBJS = $(SIMPLE_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
FSIEVE_OBJS = $(FSIEVE_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

SIMPLE_TARGET = $(SIMPLE_BUILD_DIR)/simple_exec
FSIEVE_TARGET = $(FSIEVE_BUILD_DIR)/fsieve_exec

all: $(SIMPLE_TARGET) $(FSIEVE_TARGET)

$(SIMPLE_TARGET): $(SIMPLE_OBJS)
	@mkdir -p $(SIMPLE_BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(FSIEVE_TARGET): $(FSIEVE_OBJS)
	@mkdir -p $(FSIEVE_BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
