CC=gcc

WORKDIR=.
INCLDIR=$(WORKDIR)
VPATH=$(WORKDIR)

INCLFLAG=-I$(INCLDIR)
CFLAG=$(INCLFLAG) -c -g -Wall

all:test_upload_file

OBJ=test_upload_file.o make_log.o

test_upload_file:$(OBJ)
	$(CC) $^ -o $@
	
.c.o:
	$(CC) $(CFLAG) $<

.PHONY:all clean

clean:
	-rm -f *.o test_upload_file
