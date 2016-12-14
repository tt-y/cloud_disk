CC=gcc

WORKDIR=.
INCLDIR=$(WORKDIR)
VPATH=$(WORKDIR)

INCLFLAG=-I$(INCLDIR) -I/usr/local/include/hiredis
CFLAG=$(INCLFLAG) -c -g -Wall
LIBS=-lhiredis

all:fdfs_upload_test redis_example redis_op_test

fdfs_upload_test:fdfs_upload_test.o make_log.o
	$(CC) $^ -o $@

redis_example:redis_example.o
	$(CC) $^ -o $@ $(LIBS)
	
redis_op_test:redis_op_test.o redis_op.o make_log.o
	$(CC) $^ -o $@ $(LIBS)
	
.c.o:
	$(CC) $< $(CFLAG)

.PHONY:all clean

clean:
	-rm -f *.o fdfs_upload_test redis_example redis_op_test
