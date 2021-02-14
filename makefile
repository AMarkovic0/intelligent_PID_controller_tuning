CC = gcc
CFLAGS = -g -Wall -o
LIBS = -lm

CFILES = ./lib/gen_alg.c main.c
OUTFILE = main

all: app

app:
        $(CC) $(CFLAGS) $(OUTFILE) $(CFILES) $(LIBS) -I.

clear:
        rm *.o
