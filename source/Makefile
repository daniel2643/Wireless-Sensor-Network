all: wsn

SHELL = /bin/sh
CC = mpicc
RUN = mpirun
CFLAGS += -c

wsn: main.o master.o slave.o
	$(CC) -w -std=c11 -o wsn main.o master.o slave.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

master.o: master.c
	$(CC) $(CFLAGS) master.c

slave.o: slave.c
	$(CC) $(CFLAGS) slave.c


.PHONY: clean
clean:	
	rm -f .DS*
	rm -f *.o
	rm -f *.log
	rm -f wsn
	
run:
	export OMPI_MCA_btl_vader_backing_directory=/tmp
	$(RUN) -np 21 --oversubscribe wsn

one:
	make clean
	make
	make run
