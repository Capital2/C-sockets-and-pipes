CC = gcc
CFLAGS = -Wall -g

all: Server Client

Server: Server.c
	$(CC) $(CFLAGS) -o $@ $^

Client: Client.c
	$(CC) $(CFLAGS) -o $@ $^

Test: Client Test.c launch_server
	$(CC) $(CFLAGS) -o $@ Test.c
	./Test
	echo 'Test successful!'
	pkill "Server"

launch_server : FORCE Server
	./Server &

FORCE: ;

clean:
	rm -f Server Client Test
	rm fifo1 fifo2

