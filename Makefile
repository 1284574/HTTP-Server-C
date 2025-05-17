CC = gcc
RM = rm -f

default: all

all: client server

client: client.c
	$(CC) -o client client.c

server: server.c
	$(CC) -o server server.c

clean:
	$(RM) client server