CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lGL -lGLU -lglut

TARGET = monitor

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)