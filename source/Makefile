all: wsn

SHELL = /bin/sh
CC = mpicc
RUN = mpirun
CFLAGS += -c

wsn: main.o master.o slave.o
	$(CC) -Wall -o wsn main.o master.o slave.o

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
	rm -f message_stat.txt
	rm -f result.txt
	rm -f log.txt
	rm -f wsn
	
run:
	$(RUN) -np 21 --oversubscribe wsn

one:
	make clean
	make
	make run
