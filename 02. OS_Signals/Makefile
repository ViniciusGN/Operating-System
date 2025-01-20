TARGET1 = periodic
# TARGET2 = graphic

CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11
INCLUDE_DIR = include
SRC_DIR = src
FILE_DIR = files
BUILD_DIR = bin

SRCS1 = $(SRC_DIR)/main.c $(SRC_DIR)/sin_cos.c $(SRC_DIR)/sin_cos_g.c
# SRCS2 = $(SRC_DIR)/sin_cos_g.c
OBJS1 = $(SRCS1:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
# OBJS2 = $(SRCS2:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET1) # $(TARGET2)

$(TARGET1): $(OBJS1)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET1) $(OBJS1) -lm

# $(TARGET2): $(OBJS2)
#	@mkdir -p $(BUILD_DIR)
#	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET2) $(OBJS2)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

# $(BUILD_DIR)/$(TARGET2)

.PHONY: all clean