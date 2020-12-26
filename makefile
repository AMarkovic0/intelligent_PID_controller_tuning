CC = gcc
CFLAGS = -L"lib/" -g -Wall -o
LIBS = -lm -ls

CFILES = main.c 
OUTFILE = main

LIBSRC = gen_alg.c
LIBH = gen_alg.h

all: lib app

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
