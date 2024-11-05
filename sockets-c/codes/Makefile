
#Compilator
CC=gcc

#Flasgs
CFLAGS=-Wall -pthread

all: client.o server-select.o server-thread.o server.o showip.o

client.o:
	@echo Comp. Client
	$(CC) $(CFLAGS) client.c -o client

server-select.o:
	@echo Comp. Server
	$(CC) $(CFLAGS) server-select.c -o server-select

server-thread.o:
	@echo Comp. Server
	$(CC) $(CFLAGS) server-thread.c -o server-thread

server.o:
	@echo Comp. Server
	$(CC) $(CFLAGS) server.c -o server

showip.o:
	@echo Comp. Server
	$(CC) $(CFLAGS) showip.c -o showip

clean:
	rm -rf client server server-thread server-select *.o *.out