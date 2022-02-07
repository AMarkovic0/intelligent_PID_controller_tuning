CC = gcc
TARGET = main
MAINFILE = main.c

SRCDIR = ./src/
INCDIRS = ./inc/

SRCFILES = gen_alg.c

SRC = ./$(MAINFILE) $(addprefix $(SRCDIR), $(SRCFILES))
INC = $(addprefix -I, $(INCDIRS))
LIB = $(addprefix -L, $(LIBDIRS))
LINK = -lm

CFLAGS = $(LIB) $(INC) $(LINK)

all:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

run:
	./$(TARGET)

clean:
	rm ./$(TARGET)

