# vim: ts=4:noexpandtab:
# Makefile for m68k-atari-mint-gcc

OBJEXT = o

include source.mak

CC=m68k-atari-mint-gcc
AS=m68k-atari-mint-as -m68000
AR=m68k-atari-mint-ar

CMINI_LIB=/opt/libcmini/lib
CMINI_INC=/opt/libcmini/include
CMINI_MINT_INC=/opt/libcmini/include/mint

CFLAGS=--std=gnu99 -O2 -s -DTOS \
	-nostdinc -I$(CMINI_INC) -I$(CMINI_MINT_INC) \
	-nostdlib -L$(CMINI_LIB)

ctags.ttp: $(OBJECTS) tmpfile.o
	$(CC) $(CFLAGS) -o ctags.ttp $(CMINI_LIB)/crt0.o $(OBJECTS) tmpfile.o \
	-lcmini -lgcc 

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $*.c \
	-lcmini -lgcc 
