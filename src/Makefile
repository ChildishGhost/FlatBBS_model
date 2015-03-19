# ------------------------------------------------------ #
#  Makefile	( FlatBBS Ver 0.0.1 )                        #
# ------------------------------------------------------ #
#  author : childish.tw                                  #
#  target : Makefile for FlatBBS main source             #
# ------------------------------------------------------ #

CC	= clang
CFLAGS = -O2 -std=c11 -I../include -Wall -Wextra -pedantic
LDFLAGS	= -lzmq -ljansson `pkg-config --libs --cflags icu-uc icu-io`

SRC		= model.c api.c json.c struct.c board.c user.c
OBJ		= model.o api.o json.o struct.o board.o user.o
EXE		= model


.PHONY: clean

all: model

model: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f $(EXE) *.o

