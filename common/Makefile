# Makefile for CS50 'common' library
#   Builds and compiles utility functions into a library.
#
# David Kotz, April 2016, July 2017, April 2019, 2021
# updated by Xia Zhou, July 2016
# Further updated for CS50 Indexer Lab

# Object files and the target library
OBJS = pagedir.o index.o word.o
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

# Build $(LIB) by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
pagedir.o: pagedir.c pagedir.h
index.o: index.c index.h
word.o: word.c word.h

.PHONY: clean sourcelist

# List all the sources and docs in this directory
sourcelist: Makefile *.md *.c *.h
	@echo $^

# Clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
