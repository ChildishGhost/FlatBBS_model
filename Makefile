# ------------------------------------------------------ #
#  Makefile	( FlatBBS Ver 0.0.1 )                        #
# ------------------------------------------------------ #
#  author : childish.tw                                  #
#  target : Makefile for FlatBBS (top level)             #
# ------------------------------------------------------ #

all: include/config.h
	@cd src; make

include/config.h:
	@echo Please copy and modify \`include/config.h.sample\` to \`include/config.h\`
	@false

clean:
	@cd src; make clean
