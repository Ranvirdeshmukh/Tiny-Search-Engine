# Makefile for 'indexer' module
# Ranvir Deshmukh, CS50 Lab 5

# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common -I../libcs50

# Executable names
PROG1 = indexer
PROG2 = indextest
PROGS = $(PROG1) $(PROG2)

# Object files
OBJS1 = indexer.o
OBJS2 = indextest.o
LIBS = ../common/common.a ../libcs50/libcs50-given.a

.PHONY: all clean

# Default: build both programs
all: $(PROGS)

# Build rules for the two programs
$(PROG1): $(OBJS1) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

$(PROG2): $(OBJS2) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

# Dependencies
indexer.o: indexer.c ../common/pagedir.h ../common/index.h ../common/word.h
indextest.o: indextest.c ../common/index.h

# Cleaning up
clean:
	rm -f *~
	rm -f *.o
	rm -f core
	rm -f $(PROGS)


