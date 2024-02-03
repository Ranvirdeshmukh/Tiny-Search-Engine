# Makefile for 'crawler' module
# Ranvir Deshmukh, CS50 Lab 4



# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50-given -I../common

# Name of the executable to build
PROG = crawler

# Object files that make up the program
OBJS = crawler.o
LIBS = ../common/common.a ../libcs50/libcs50-given.a

# Build the program
$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

# Dependencies: object files depend on header files
crawler.o: crawler.c
../common/pagedir.o: ../common/pagedir.h

# Phony targets for cleaning and making a list of sources
.PHONY: clean sourcelist

# Clean command
clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)

# Command to list sources (for the professor's use in preparing starter kits)
sourcelist:
	@echo Makefile *.c *.h
