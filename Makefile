CC=gcc

WORKDIR=.
INCLDIR=$(WORKDIR)/incl
VPATH=$(WORKDIR)/src

INCLFLAG=-I$(INCLDIR)
CFLAG=$(INCLFLAG) -c -g -Wall

all:main

OBJ=main.o make_log.o

main:$(OBJ)
	$(CC) $^ -o $@
	
.c.o:
	$(CC) $(CFLAG) $<

.PHONY:all clean

clean:
	-rm -f *.o main