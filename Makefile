CC = gcc
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -D_POSIX_C_SOURCE=200809L
CFLAGS = -std=c99 -pedantic -Wall -o3 -g $(CPPFLAGS)

# Raylib location (adjust as needed)
RAYLIB_DIR = ./raylib-5.0_linux_amd64
INCLUDE_FLAGS = -I$(RAYLIB_DIR)/include
LDFLAGS = -L$(RAYLIB_DIR)/lib/ -Wl,-rpath=$(RAYLIB_DIR)/lib -lraylib -lGL -lm -lpthread -ldl -lrt

# Source files and output
SRCS = src/main.c 
TARGET = build/muditor

# Default target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gf2 $(TARGET)
.PHONY: all clean run

