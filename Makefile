CC=gcc
CFLAGS=-g -c -Wall -Werror -Iinclude
LDFLAGS= # nothing for now but maybe in the future 

SRC_DIR=src
BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj

# Search the source directory for relevant files
SOURCES=$(wildcard $(SRC_DIR)/*.c)

# Convert the list of source files into a list of object files. The object files are placed in the obj directory inside build.
OBJECTS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

EXECUTABLE=$(BUILD_DIR)/prog

all: $(EXECUTABLE)

# Link the object files to produce the executable.
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(@D)  # Ensure the directory for the executable exists.
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Rule for building object files. Note the use of automatic variables.
# $< is the name of the prerequisite (source file) and $@ is the name of the target.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)  # Ensure the obj directory exists.
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)
