CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Raylib location (adjust as needed)
RAYLIB_DIR = ./raylib-5.0_linux_amd64
INCLUDE_FLAGS = -I$(RAYLIB_DIR)/include
LDFLAGS = -L$(RAYLIB_DIR)/lib/ -Wl,-rpath=$(RAYLIB_DIR)/lib -lraylib -lGL -lm -lpthread -ldl -lrt

# Source files and output
SRCS = src/main.c
TARGET = src/main

# Default target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

