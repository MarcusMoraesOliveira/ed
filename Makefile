EXECUTABLE = bin/tp3.out
CC = g++
CFLAGS = -g -std=c++11 -I$(INCLUDE_DIR)

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

MKDIR_P = mkdir -p

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(MKDIR_P) $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)  # Use LDFLAGS for linker flags

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) 

clean:
	rm -rf bin/* obj/*

.PHONY: all clean