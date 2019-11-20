# Makefile for ex1-q1 winter 2019A

CFLAGS=-Wall
LDFLAGS=-lm #not raelly needed for this exercise 
CC=gcc -std=c99
OBJFILES=ex1_q1.o
ECHO=echo "going to compile for target $@"
OS := $(shell uname)
ifneq (,$(findstring CYGWIN_NT,$(OS)))
EXT = .exe
else
EXT =
endif

PROG = ex1_q1$(EXT)

all: $(PROG) test

%.o: %.c %.h 
	$(ECHO) ex1_q1.c 
	$(CC) $(CFLAGS) -c $< -o $@
$(PROG): $(OBJFILES)
	echo 'going to build (link) ex1_q1...'		
	gcc -o $(PROG) -Wall $(OBJFILES)
clean:
	rm -vf *.o $(PROG) *.log

test:
	@echo going to run test...
	# make sure you have input file in.txt
	# so that the following command works.
	./$(PROG) < in.txt > out.log