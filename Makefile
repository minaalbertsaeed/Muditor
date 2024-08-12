CC = gcc

CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -D_POSIX_C_SOURCE=200809L
CFLAGS = -std=c99 -Wno-pedantic -Wall -O3 -g $(CPPFLAGS)

MUDITOR_DIR   = ./build/libmuditor.so
RAYLIB_DIR 	  = ./raylib-5.0_linux_amd64
INCLUDE_FLAGS = -I$(RAYLIB_DIR)/include
LDFLAGS       = -L$(RAYLIB_DIR)/lib/ -Wl,-rpath=$(RAYLIB_DIR)/lib -lraylib \
                -lGL -lm -lpthread -ldl -lrt 
                # -L$(MUDITOR_DIR)/ -Wl,-rpath=$(MUDITOR_DIR)/ -lmuditor \

# Source files and output
SRCS 		= src/main.c 
TARGET 		= build/main
MUDITOR_SRC = src/libmuditor/libmuditor.c

# Default target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)


clean:
	rm -f $(TARGET)

lib:
	$(CC) -fPIC -shared $(CFLAGS) $(INCLUDE_FLAGS) $(LDFLAGS) $(MUDITOR_SRC) -o $(MUDITOR_DIR)

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gf2 ./$(TARGET)

.PHONY: all clean run lib debug

