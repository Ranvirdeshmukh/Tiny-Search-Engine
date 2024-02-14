# Makefile for 'querier' module
# Ranvir Deshmukh, CS50 Lab 6

# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common -I../libcs50

# Executable name
PROG = querier

# Object files
OBJS = querier.o
LIBS = ../common/common.a ../libcs50/libcs50.a

.PHONY: all clean

# Default: build the program
all: $(PROG)

# Build rule for the program
$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

# Dependencies
querier.o: querier.c ../common/pagedir.h ../common/index.h ../common/word.h

# Cleaning up
clean:
	rm -f *~
	rm -f *.o
	rm -f core
	rm -f $(PROG)
