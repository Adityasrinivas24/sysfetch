# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source files
SRCS = sysfetch.c

# Executable name
EXEC = system

# Libraries
LIBS = -lm

# Build and run the executable
.PHONY: sys
sys: $(EXEC)
	./$(EXEC)

# Compile and link the source files
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) $(LIBS)

# Clean the project
.PHONY: clean
clean:
	rm -f $(EXEC)

