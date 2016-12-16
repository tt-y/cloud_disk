CC=gcc

WORKDIR=.
INCLDIR=$(WORKDIR)/incl
VPATH=$(WORKDIR)/src

INCLFLAG=-I$(INCLDIR)
CFLAG=$(INCLFLAG) -c -g -Wall
LIBFLAG=-lfcgi

all:upload_cgi

upload_cgi:upload_cgi.o
	$(CC) $^ -o $@ $(LIBFLAG)
	
.c.o:
	$(CC) $< $(CFLAG)

.PHONY:all clean

clean:
	-rm -f *.o upload_cgi
