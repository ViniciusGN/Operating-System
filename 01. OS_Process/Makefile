TARGET1 = iplot
TARGET2 = complement

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
INCLUDE_DIR = include
SRC_DIR = src
FILE_DIR = files
BUILD_DIR = build

SRCS1 = $(SRC_DIR)/main.c $(SRC_DIR)/iplot.c
SRCS2 = $(SRC_DIR)/complement.c
OBJS1 = $(SRCS1:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS2 = $(SRCS2:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET1) $(OBJS1)

$(TARGET2): $(OBJS2)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET2) $(OBJS2)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(TARGET1) $(BUILD_DIR)/$(TARGET2)

.PHONY: all clean
