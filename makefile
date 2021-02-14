CC = gcc
CFLAGS = -g -Wall -o -I .
LIBS = -lm

CFILES = ./src/gen_alg.c main.c 
OUTFILE = main

all: app

app:
	$(CC) $(CFLAGS) $(OUTFILE) $(CFILES) $(LIBS)

lib:
	cd ./inc/; \
	$(CC) -c -g $(LIBSRC); \
	ar rs libs.a *.o; \
	rm *.o; \
	cd ..

clear:
	rm *.o
