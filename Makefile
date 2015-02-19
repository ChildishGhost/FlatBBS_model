# ------------------------------------------------------ #
#  Makefile	( FlatBBS Ver 0.0.1 )                        #
# ------------------------------------------------------ #
#  author : childish.tw                                  #
#  target : Makefile for FlatBBS (top level)             #
# ------------------------------------------------------ #

all:
	#@cd lib; make
	@cd src; make
	#@cd util; make

clean:
	#@cd lib; make clean
	@cd src; make clean
	#@cd util; make clean
