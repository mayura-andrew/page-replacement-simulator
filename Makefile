# Makefile for Page Replacement Simulator
# For Turbo C Compiler

# Compiler
CC=tcc

# Compiler flags
CFLAGS=-I.

# Target executable
TARGET=pagerep.exe
TEST_TARGET=test.exe

# Source files
SOURCES=main.c graphics.c algorithm.c
OBJECTS=main.obj graphics.obj algorithm.obj

# Header files
HEADERS=config.h types.h graphics.h algorithm.h

# Default target
all: $(TARGET)

# Build modular version
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Build object files
main.obj: main.c $(HEADERS)
	$(CC) -c $(CFLAGS) main.c

graphics.obj: graphics.c graphics.h types.h config.h
	$(CC) -c $(CFLAGS) graphics.c

algorithm.obj: algorithm.c algorithm.h types.h config.h
	$(CC) -c $(CFLAGS) algorithm.c

# Build standalone test version
test: test.c
	$(CC) test.c -o $(TEST_TARGET)

# Clean build files
clean:
	del *.obj
	del *.exe
	del *.bak

# Rebuild everything
rebuild: clean all

.PHONY: all test clean rebuild
