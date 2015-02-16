# ------------------------------------------------------ #
#  Makefile	( FlatBBS Ver 0.0.1 )                        #
# ------------------------------------------------------ #
#  author : childish.tw                                  #
#  target : Makefile for FlatBBS main source             #
# ------------------------------------------------------ #

CC	= clang
CFLAGS = -O2 -std=c11 -I../include

SRC		= model.c
OBJ		= model.o
EXE		= model


.PHONY: clean

all: model

model: $(OBJ)
		$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f $(EXE) *.o

