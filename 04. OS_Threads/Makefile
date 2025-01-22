CC=gcc
CFLAGS=-Wall -Wextra -ansi -pedantic -c -std=c99
LDFLAGS=-lpthread
INCLUDE_PATH=./include
SRC_PATH=./src
CPPFLAGS=-I$(INCLUDE_PATH)
OBJS=$(SRC_PATH)/main.o $(SRC_PATH)/matrix_product.o
EXEC=./bin/matrix_product

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(SRC_PATH)/%.o: $(SRC_PATH)/%.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

clean:
	rm $(SRC_PATH)/*.o

mrproper: clean
	rm $(EXEC)
