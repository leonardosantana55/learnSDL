##-----------------------------------------------#
## Makefile for UNIX systems #
## using a GNU C compiler #
##-----------------------------------------------#
##
## Compiler flags:
## -g -- Enable debugging
## -Wall -- Turn on all warnings (not used since it gives away
## the bug in this program)
## -D__USE_FIXED_PROTOTYPES__
## -- Force the compiler to use the correct headers
## -ansi -- Don't use GNU extensions. Stick to ANSI C.

CC=gcc
#CFLAGS=-g -D__USE_FIXED_PROTOTYPES__ -ansi
# OBJS: All the files to be compiled:
OBJS=hello.c
LINKER_FLAGS=-lSDL2
OBJ_NAME=prog

all:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OBJ_NAME) $(LINKER_FLAGS)
clean:
	rm -f $(OBJS)
